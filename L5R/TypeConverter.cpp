#include <string>
#include "TypeConverter.h"
#include "cards/Card.h"
#include "cards/Personality.h"
#include "cards/Holding.h"
#include "cards/Follower.h"
#include "cards/Item.h"

enum type{PERSONALITY = 1, HOLDING, FOLLOWER, ITEM};



void TypeConverter::getCorrectType(BlackCard *card, Personality *& person, Holding *& hold)
{
	if (card->getType() == PERSONALITY) {
		(person)=dynamic_cast<Personality*>(card);
		(hold) = NULL;
	}
	else {
		(hold)=dynamic_cast<Holding*>(card);
		(person) = NULL;
	}
}

void TypeConverter::getCorrectType(GreenCard *card, Follower *& follow, Item *& item)
{
	if (card->getType() == FOLLOWER) {
		(follow)=dynamic_cast<Follower*>(card);
		(item) = NULL;
	}
	else {
		(item)=dynamic_cast<Item*>(card);
		(follow) = NULL;
	}
}
