#ifndef TypeConverter_h
#define TypeConverter_h

class Personality;
class Holding;
class Item;
class Follower;
class GreenCard;
class BlackCard;

class TypeConverter{

	public:
		
		static void getCorrectType(BlackCard *card, Personality *& person, Holding *& hold);
		static void getCorrectType(GreenCard *card, Follower *& follow, Item *& item);
		
};

#endif