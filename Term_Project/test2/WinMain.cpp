#include "pch.h"

#include <iostream>
#include <Windows.h>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Dice.hpp"
#include "Piece.hpp"
#include "Player.hpp"
#include "GameBoard.hpp"
#include "Menu.hpp"
#include "Sound.hpp"
#include "Text.hpp"
#include "Game.hpp"
#include "DiceRollButton.hpp"
#include "DicePanel.hpp"
#include "Turn.hpp"
#include "PlayerIcon.hpp"
#include "StartMenu.hpp"
#include "BoardPlate.hpp"

int isWin(Player* player[]) {

	for (int i = 1; i <= RULE_playerPlayingNumber; i++)
	{
		if (player[i]->getScore() >= RULE_WinScore)
			return i;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

StartMenuPoint:

	sf::RenderWindow startWindow(sf::VideoMode(1000, 667), GAME_TITLE);
	sf::Vector2i MousePosition;
	sf::Event MenuEvent;
	StartMenu startMenu(WINDOW_SIZE_X, WINDOW_SIZE_Y);

	while (startWindow.isOpen())
	{
		while (startWindow.pollEvent(MenuEvent))
		{
			switch (MenuEvent.type)
			{

				// 창 닫기 이벤트
			case sf::Event::Closed: {

				exit(0);
				break;

			}
			case sf::Event::KeyPressed: {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) startMenu.moveUp();

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) startMenu.moveDown();

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

					switch (startMenu.getSelectedItemIndex()) {

					case StartMenu::BUTTON_PLAY:

						startWindow.close();
						goto GameStartingPoint;
						break;

					case StartMenu::BUTTON_OPTION:
	
						Sleep(140);
						break;

					case StartMenu::BUTTON_QUIT:
						exit(0);
						break;
					}
				}
			}

			}

			startWindow.clear();
			startMenu.draw(startWindow);
			startWindow.display();
		}
	}

GameStartingPoint:

	// 게임 초기화
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), GAME_TITLE);
	sf::Event event;
	Menu menu(WINDOW_SIZE_X, WINDOW_SIZE_Y);

	PlayerIcon *icons[RULE_playerPlayingNumber + 1]; // RULE_playerPlayingNumber = 4
	Player *player[RULE_playerPlayingNumber + 1];
	std::string str;

	for (int i = 1; i <= RULE_playerPlayingNumber; i++) {
		str = std::to_string(i);
		icons[i] = new PlayerIcon(window, str, TEXT_showPlayerInformation_X - 95, (TEXT_showPlayerInformation_Y + (i - 1) * 120));
		player[i] = new Player(window, str);
	}

	GameBoard background(window);
	Turn turn_ins;
	Dice *rollDice;

	// 주사위 버튼
	DiceRollButton diceButton(window);

	// 주사위 패널
	DicePanel dicePanel(window);

	// 사운드 관리 객체
	Sound* soundManage = Sound::getInstance();
	soundManage->PlayBackGroundMusic();

	// 폰트, 텍스트 관리 객체
	Text *textManage = Text::getInstance();

	// 발판 관리 객체
	BoardPlate* boardManage = BoardPlate::getInstance();

	int turn = turn_ins.getTurn() % RULE_playerPlayingNumber;
	if (turn == 0) turn = RULE_playerPlayingNumber;

	textManage->drawTextArgu(turn, TURN_NUMBER, turn_ins.getTurn());

	bool istime = false;


GameProcessing:

	while (window.isOpen())
	{
		// 승리 조건
		if (isWin(player) > 0) {
			textManage->drawTextArgu(isWin(player), 10, turn_ins.getTurn());
			window.clear();
			window.draw(background.getSprite());

			for (int i = 1; i <= RULE_playerPlayingNumber; i++) {
				window.draw(icons[i]->getSprite()); // 각 플레이어의 아이콘 draw
			}

			window.draw(textManage->getText(TURN_NUMBER));
			window.display();
			Sleep(4000);

			break;
		}

		else {
			while (window.pollEvent(event))
			{
				switch (event.type)
				{

					// 창 닫기 이벤트
				case sf::Event::Closed: {

					window.close();
					break;
				}

					// 키보드 클릭 이벤트
				case sf::Event::KeyPressed: {

					// 게임 메뉴 호출
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

						soundManage->PauseBackGroundMusic();

						while (window.isOpen()) {

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) menu.moveUp();

							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) menu.moveDown();

							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

								switch (menu.getSelectedItemIndex()) {

								case Menu::BUTTON_PLAY:
									soundManage->PlayBackGroundMusic();
									goto GameProcessing;
									break;

								case Menu::BUTTON_GOTOTITLE:

									goto StartMenuPoint;
									Sleep(140);
									break;

								case Menu::BUTTON_QUIT:
									window.close();
									break;
								}

							}

							window.clear();
							menu.draw(window);
							window.display();

						}
					} // end of 게임 메뉴 호출

				} // end of 키보드 클릭 이벤트


				  // 마우스 클릭 이벤트
				case sf::Event::MouseButtonPressed:
					std::cout << "Moust button has been pressed" << std::endl;
					MousePosition = sf::Mouse::getPosition(window);

					int turn = turn_ins.getTurn() % RULE_playerPlayingNumber;
					if (turn == 0)
						turn = RULE_playerPlayingNumber;

					textManage->drawTextArgu(turn, TURN_NUMBER, turn_ins.getTurn());

					if (istime) {

						for (int i = 0; i < 40; i++)
							/*
								타임머신을 이용해 원하는 발판으로 이동
							*/
							if (boardManage->getBoard(i).isInBoard(MousePosition)) {
								int moveNum = 0;
								if (i > 30)
									moveNum = i - 30;
								if (i < 30)
									moveNum = i + 10;

								for (int j = 0; j < moveNum; j++) {

									if ((turn_ins.getTurn() - 1) % RULE_playerPlayingNumber != 0) {
										player[(turn_ins.getTurn() - 1) % RULE_playerPlayingNumber]->OwnPiece->MovePiece();
										boardManage->whenPassStart(*player[(turn_ins.getTurn() - 1) % RULE_playerPlayingNumber]);
									}
									else {
										player[RULE_playerPlayingNumber]->OwnPiece->MovePiece();
										boardManage->whenPassStart(*player[RULE_playerPlayingNumber]);
									}
								}

								if ((turn_ins.getTurn() - 1) % RULE_playerPlayingNumber != 0) {
									istime = boardManage->whenPieceOnBoard(*player[(turn_ins.getTurn() - 1) % RULE_playerPlayingNumber]);
								}
								else {
									istime = boardManage->whenPieceOnBoard(*player[RULE_playerPlayingNumber]);
								}


							}
					}

					// '주사위 굴리기' 버튼 클릭

					if (diceButton.isInButton(MousePosition)) {

						// 버튼 클릭 사운드 
						soundManage->PlayButtonClickedSound();

						// 한 턴 동안 사용할 난수 생성
						rollDice = new Dice();

						int turn = turn_ins.getTurn() % RULE_playerPlayingNumber;

						if (turn == 0) turn = RULE_playerPlayingNumber;

						// 해당 플레이어가 Sleep 상태에 있지 않은 경우

						if ((player[turn]->getSleep()) == false) {

							// 한 칸 움직이고 난 후의 Object들을 draw 
							for (int i = 0; i < rollDice->getMoveNumber(); i++) {

								if (turn_ins.getTurn() % RULE_playerPlayingNumber != 0) {
									player[turn_ins.getTurn() % RULE_playerPlayingNumber]->OwnPiece->MovePiece();
									boardManage->whenPassStart(*player[turn_ins.getTurn() % RULE_playerPlayingNumber]);
								}
								else {

									// 시작점을 통과할 때
									player[RULE_playerPlayingNumber]->OwnPiece->MovePiece();
									boardManage->whenPassStart(*player[RULE_playerPlayingNumber]);
								}

								window.clear();

								window.draw(background.getSprite());
								window.draw(dicePanel.getDice1Sprite(*rollDice));
								window.draw(dicePanel.getDice2Sprite(*rollDice));
								window.draw(textManage->getText(TURN_NUMBER));

								boardManage->drawAllBoard(window);
								textManage->drawText(window);

								for (int i = 1; i <= RULE_playerPlayingNumber; i++) {
									window.draw(player[i]->OwnPiece->getSprite());
									window.draw(icons[i]->getSprite());
								}

			
								window.display();
								soundManage->PlayPieceMoveSound();
								Sleep(PIECE_MOVING_TIME);
							}

							if ((turn_ins.getTurn()) % RULE_playerPlayingNumber != 0) {
								std::cout << "플레이어" << ((turn_ins.getTurn()) % RULE_playerPlayingNumber) << " ";
								istime = boardManage->whenPieceOnBoard(*player[(turn_ins.getTurn()) % RULE_playerPlayingNumber]);
							}
							else {
								std::cout << "플레이어" << (RULE_playerPlayingNumber) << " ";
								istime = boardManage->whenPieceOnBoard(*player[RULE_playerPlayingNumber]);
							}


						}
						else {
							player[turn]->setSleep(player[turn]->getSleep() - 1);
							std::cout << player[turn]->getSleep() << std::endl;
						}
						boardManage->playerScore(player);

						delete rollDice;

						turn_ins.IncTurn();

					}
					/*
					turn = turn_ins.getTurn() % 4;
					if (turn == 0)
						turn = 4;
					*/

					turn = turn_ins.getTurn() % RULE_playerPlayingNumber;
					if (turn == 0)
						turn = RULE_playerPlayingNumber;

				
					textManage->drawTextArgu(turn, TURN_NUMBER, turn_ins.getTurn());

					break;
				}

			} // end of while (window.pollEvent(event))

			window.clear();

			window.draw(background.getSprite());
			boardManage->drawAllBoard(window);
			textManage->drawText(window);
			window.draw(diceButton.getSprite());
			window.draw(textManage->getText(TURN_NUMBER));

			for (int i = 1; i <= RULE_playerPlayingNumber; i++) {
				window.draw(player[i]->OwnPiece->getSprite());
				window.draw(icons[i]->getSprite());
			}
			window.display();

		} // end of while (window.isOpen())
	}
}


