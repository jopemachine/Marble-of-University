#ifndef MAPPOINT_HPP
#define MAPPOINT_HPP

#include "SFML/Graphics.hpp"
#include "Game.hpp"
static sf::Vector2f MapPoint[FOOTHOLD_NUMBER] = {

	/*00MapPoint*/ {_X - nd * 0 - sd * 0, _Y - nd * 0 - sd * 0},

	// x��ǥ���� �����մϴ�.
	// MapPoint[10]�� Ư�� ����

	/*01MapPoint*/ {_X - nd * 1 - sd * 0, _Y - nd * 0 - sd * 0},
	/*02MapPoint*/ {_X - nd * 2 - sd * 0, _Y - nd * 0 - sd * 0},
	/*03MapPoint*/ {_X - nd * 3 - sd * 0, _Y - nd * 0 - sd * 0},
	/*04MapPoint*/ {_X - nd * 4 - sd * 0, _Y - nd * 0 - sd * 0},
	/*05MapPoint*/ {_X - nd * 5 - sd * 0, _Y - nd * 0 - sd * 0},
	/*06MapPoint*/ {_X - nd * 6 - sd * 0, _Y - nd * 0 - sd * 0},
	/*07MapPoint*/ {_X - nd * 7 - sd * 0, _Y - nd * 0 - sd * 0},
	/*08MapPoint*/ {_X - nd * 8 - sd * 0, _Y - nd * 0 - sd * 0},
	/*09MapPoint*/ {_X - nd * 9 - sd * 0, _Y - nd * 0 - sd * 0},
	/*10MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 0 - sd * 0},

	// y��ǥ���� �����մϴ�.
	// MapPoint[20]�� Ư�� ����

	/*11MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 0 - sd * 1},
	/*12MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 1 - sd * 1},
	/*13MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 2 - sd * 1},
	/*14MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 3 - sd * 1},
	/*15MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 4 - sd * 1},
	/*16MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 5 - sd * 1},
	/*17MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 6 - sd * 1},
	/*18MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 7 - sd * 1},
	/*19MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 8 - sd * 1},
	/*20MapPoint*/ {_X - nd * 9 - sd * 1, _Y - nd * 9 - sd * 1},

	// x��ǥ���� �����մϴ�.
	// MapPoint[30]�� Ư�� ����

	/*21MapPoint*/ { MapPoint[9].x, MapPoint[20].y},
	/*22MapPoint*/ { MapPoint[8].x, MapPoint[20].y},
	/*23MapPoint*/ { MapPoint[7].x, MapPoint[20].y},
	/*24MapPoint*/ { MapPoint[6].x, MapPoint[20].y},
	/*25MapPoint*/ { MapPoint[5].x, MapPoint[20].y},
	/*26MapPoint*/ { MapPoint[4].x, MapPoint[20].y},
	/*27MapPoint*/ { MapPoint[3].x, MapPoint[20].y},
	/*28MapPoint*/ { MapPoint[2].x, MapPoint[20].y},
	/*29MapPoint*/ { MapPoint[1].x, MapPoint[20].y},
	/*30MapPoint*/ { MapPoint[0].x, MapPoint[20].y},

	// y��ǥ���� �����մϴ�.

	/*31MapPoint*/ {MapPoint[0].x, MapPoint[19].y},
	/*32MapPoint*/ {MapPoint[0].x, MapPoint[18].y},
	/*33MapPoint*/ {MapPoint[0].x, MapPoint[17].y},
	/*34MapPoint*/ {MapPoint[0].x, MapPoint[16].y},
	/*35MapPoint*/ {MapPoint[0].x, MapPoint[15].y},
	/*36MapPoint*/ {MapPoint[0].x, MapPoint[14].y},
	/*37MapPoint*/ {MapPoint[0].x, MapPoint[13].y},
	/*38MapPoint*/ {MapPoint[0].x, MapPoint[12].y},
	/*39MapPoint*/ {MapPoint[0].x, MapPoint[11].y},


};

#endif