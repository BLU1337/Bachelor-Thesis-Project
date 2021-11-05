#include "MunchkinCards.h"

using namespace std;



MunchkinCard::MunchkinCard(
		int _markerID,
		const string & _cardName,
		const string & _effect,
		const string & _badThings,
		const string & _itemEffect,
		const string & _itemNeeds,
		vector<string> _bonis,
		ParentCardType _parentCardType,
		CardType _type,
		ItemType _itemType,
		int _strengthBoni,
		int _debuff,
		int _monsStrength,
		int _lvlUp,
		int _treasures,
		int _itemValue,
		int _handsNeeded,
		bool _itemLarge
	) :
		markerID(_markerID),
		cardName(_cardName),
		effect(_effect),
		bonis(_bonis),
		badThings(_badThings),
		itemType(_itemType),
		itemEffect(_itemEffect),
		itemNeeds(_itemNeeds),
		parentCardType(_parentCardType),
		type(_type),
		strengthBoni(_strengthBoni),
		debuff(_debuff),
		monsStrength(_monsStrength),
		lvlUp(_lvlUp),
		treasures(_treasures),
		itemValue(_itemValue),
		handsNeeded(_handsNeeded),
		itemLarge(_itemLarge)
{
}

vector<MunchkinCard> MunchkinCard::cardsConstr() {
	vector<MunchkinCard> cards;


	MunchkinCard card0;
	card0.markerID = 0;
	card0.cardName = "Ueberlebe Ragnar\x94k";
	card0.parentCardType = ParentCardType::treasure;
	card0.type = CardType::lvlUp;
	card0.lvlUp = 1;

	MunchkinCard card1;
	card1.markerID = 1;
	card1.cardName = "Bermudashorts der Unverwundbarkeit";
	card1.parentCardType = ParentCardType::treasure;
	card1.type = CardType::item;
	card1.itemType = ItemType::clothing;
	card1.itemNeeds = "Nicht von Kriegern nutzbar";
	card1.strengthBoni = 4;
	card1.itemValue = 400;

	MunchkinCard card2;
	card2.markerID = 2;
	card2.cardName = "FLUCH! Die Laune des Schicksals";
	card2.parentCardType = ParentCardType::door;
	card2.type = CardType::curse;
	card2.effect = "Verliere deine Klasse";
	card2.badThingsFunc = badthings::looseClass;

	MunchkinCard card3;
	card3.markerID = 3;
	card3.cardName = "Krieger";
	card3.type = CardType::munchClass;
	card3.parentCardType = ParentCardType::door;
	card3.bonis.push_back("Lege im Kampf bis zu 3 Karten ab f�r jeweils +1;");
	card3.bonis.push_back("Bei Gleichstand im Kampf gewinnst du;");

	MunchkinCard card4;
	card4.markerID = 4;
	card4.cardName = "Magisches Fagott";
	card4.parentCardType = ParentCardType::treasure;
	card4.type = CardType::item;
	card4.itemType = ItemType::weapon;
	card4.strengthBoni = 4;
	card4.itemLarge = true;
	card4.handsNeeded = 2;
	card4.itemValue = 600;

	MunchkinCard card5;
	card5.markerID = 5;
	card5.cardName = "Morgan Le Fay";
	card5.type = CardType::monster;
	card5.parentCardType = ParentCardType::door;
	card5.effect = "-4 vs Gladiators but +5 vs male Munchkins";
	card5.monsStrength = 17;
	card5.badThings = "male Munchkins die! Female Munchkins lvl--";
	card5.lvlUp = 2;
	card5.treasures = 4;
	card5.badThingsFunc = badthings::maleDeadFemaleLevelDown;

	MunchkinCard card6;
	card6.markerID = 6;
	card6.cardName = "Pfeil und Bogen des Herkules";
	card6.parentCardType = ParentCardType::treasure;
	card6.type = CardType::item;
	card6.itemType = ItemType::weapon;
	card6.bonis.push_back("Angriffe z\x84hlen als Angriff mit Feuer und Flamme");
	card6.strengthBoni = 4;
	card6.handsNeeded = 2;
	card6.itemValue = 700;

	MunchkinCard card7;
	card7.markerID = 7;
	card7.cardName = "J.R.R. Trollkin";
	card7.type = CardType::monster;
	card7.parentCardType = ParentCardType::door;
	card7.effect = "+10 vs epic Munchkins";
	card7.monsStrength = 7;
	card7.badThings = "read all following monster cards out lout until you kill a monster without help of others";
	card7.lvlUp = 1;
	card7.treasures = 2;
	card7.badThingsFunc = badthings::emptyBadThings;

	MunchkinCard card8;
	card8.markerID = 8;
	card8.cardName = "FenrisWolf";
	card8.type = CardType::monster;
	card8.parentCardType = ParentCardType::door;
	card8.monsStrength = 16;
	card8.badThings = "hands--";
	card8.lvlUp = 2;
	card8.treasures = 4;
	card8.badThingsFunc = badthings::looseHand;

	//cards[0].cardName = "FenrisWolf";
	//cards[0].type = CardType::monster;
	//cards[0].monsStrength = 16;
	//cards[0].badThings = "hands--";
	//cards[0].lvlUp = 2;
	//cards[0].treasures = 4;

	MunchkinCard card9;
	card9.markerID = 9;
	card9.cardName = "Schummeln!";
	card9.type = CardType::joker;
	card9.parentCardType = ParentCardType::door;
	card9.effect = "Lege Karte an Gegenstand du darfst diesen ausr�sten egal was die Vorraussetzungen sind";

	MunchkinCard card10;
	card10.markerID = 10;
	card10.cardName = "Zwerg";
	card10.type = CardType::race;
	card10.parentCardType = ParentCardType::door;
	card10.bonis.push_back("beliebige Anzahl gro�er Gegenst�nde;");
	card10.bonis.push_back("6 Karten auf Hand erlaubt;");

	MunchkinCard card11;
	card11.markerID = 11;
	card11.cardName = "Wunschring";
	card11.parentCardType = ParentCardType::treasure;
	card11.type = CardType::item;
	card11.itemType = ItemType::joker;
	card11.itemEffect = "beende einen Fluch";
	card11.itemValue = 500;

	MunchkinCard card12;
	card12.markerID = 12;
	card12.cardName = "von Gott gegeben";
	card12.parentCardType = ParentCardType::treasure;
	card12.type = CardType::itemBuff;
	card12.strengthBoni = 3;

	MunchkinCard card13;
	card13.markerID = 13;
	card13.cardName = "Aura der Alltäglichkeit";
	card13.type = CardType::curse;

	MunchkinCard card14;
	card14.markerID = 14;
	card14.cardName = "Die Gans die goldene Eier legt";
	card14.type = CardType::monster;

	MunchkinCard card15;
	card15.markerID = 15;
	card15.cardName = "Dieb1";
	card15.type = CardType::munchClass;

	MunchkinCard card16;
	card16.markerID = 16;
	card16.cardName = "Dieb2";
	card16.type = CardType::munchClass;

	MunchkinCard card17;
	card17.markerID = 17;
	card17.cardName = "Doppelt Gezinkter Würfel";
	card17.type = CardType::item;

	MunchkinCard card18;
	card18.markerID = 18;
	card18.cardName = "Doppelt Gezinkter Würfel2";
	card18.type = CardType::item;

	MunchkinCard card19;
	card19.markerID = 19;
	card19.cardName = "Dosenkeule";
	card19.type = CardType::item;

	MunchkinCard card20;
	card20.markerID = 20;
	card20.cardName = "Drachenhautrüstung";
	card20.type = CardType::item;

	MunchkinCard card21;
	card21.markerID = 21;
	card21.cardName = "Echt starker Bart";
	card21.type = CardType::item;

	MunchkinCard card22;
	card22.markerID = 22;
	card22.cardName = "Einherjer";
	card22.type = CardType::monster;

	MunchkinCard card23;
	card23.markerID = 23;
	card23.cardName = "Elf";
	card23.type = CardType::race;

	MunchkinCard card24;
	card24.markerID = 24;
	card24.cardName = "Elf2";
	card24.type = CardType::race;

	MunchkinCard card25;
	card25.markerID = 25;
	card25.cardName = "Faun1";
	card25.type = CardType::race;

	MunchkinCard card26;
	card26.markerID = 26;
	card26.cardName = "Faun2";
	card26.type = CardType::race;

	MunchkinCard card27;
	card27.markerID = 27;
	card27.cardName = "Fauntastische Spiele";
	card27.type = CardType::lvlUp;

	MunchkinCard card28;
	card28.markerID = 28;
	card28.cardName = "Gezinkter Würfel1";
	card28.type = CardType::item;

	MunchkinCard card29;
	card29.markerID = 29;
	card29.cardName = "Gezinkter Würfel2";
	card29.type = CardType::item;

	MunchkinCard card30;
	card30.markerID = 30;
	card30.cardName = "Gezinkter Würfel3";
	card30.type = CardType::item;

	MunchkinCard card31;
	card31.markerID = 31;
	card31.cardName = "Gezinkter Würfel4";
	card31.type = CardType::item;

	MunchkinCard card32;
	card32.markerID = 32;
	card32.cardName = "Gladiator1";
	card32.type = CardType::munchClass;

	MunchkinCard card33;
	card33.markerID = 33;
	card33.cardName = "Gladiator2";
	card33.type = CardType::munchClass;

	MunchkinCard card34;
	card34.markerID = 34;
	card34.cardName = "Gladiator3";
	card34.type = CardType::munchClass;

	MunchkinCard card35;
	card35.markerID = 35;
	card35.cardName = "Goldstandarte";
	card35.type = CardType::item;

	MunchkinCard card36;
	card36.markerID = 36;
	card36.cardName = "Grendel";
	card36.type = CardType::monster;

	MunchkinCard card37;
	card37.markerID = 37;
	card37.cardName = "Herkules";
	card37.type = CardType::monster;

	MunchkinCard card38;
	card38.markerID = 38;
	card38.cardName = "Höllentoupet";
	card38.type = CardType::item;

	MunchkinCard card39;
	card39.markerID = 39;
	card39.cardName = "Jack der Rapper";
	card39.type = CardType::monster;

	MunchkinCard card40;
	card40.markerID = 40;
	card40.cardName = "mit rot glühenden Augen";
	card40.type = CardType::joker;

	MunchkinCard card41;
	card41.markerID = 41;
	card41.cardName = "Olympisch für das Monster";
	card41.type = CardType::joker;

	MunchkinCard card42;
	card42.markerID = 42;
	card42.cardName = "Reptoid";
	card42.type = CardType::monster;

	MunchkinCard card43;
	card43.markerID = 43;
	card43.cardName = "Schummeln2";
	card43.type = CardType::joker;

	MunchkinCard card44;
	card44.markerID = 44;
	card44.cardName = "Schummeln3";
	card44.type = CardType::joker;

	MunchkinCard card45;
	card45.markerID = 45;
	card45.cardName = "Speer der Dichte";
	card45.type = CardType::item;

	MunchkinCard card46;
	card46.markerID = 46;
	card46.cardName = "Steine aus dem Styx";
	card46.type = CardType::item;

	MunchkinCard card47;
	card47.markerID = 47;
	card47.cardName = "Titanisch für das Monster";
	card47.type = CardType::joker;

	MunchkinCard card48;
	card48.markerID = 48;
	card48.cardName = "Trugbild";
	card48.type = CardType::joker;

	MunchkinCard card49;
	card49.markerID = 49;
	card49.cardName = "Unheiler Gral";
	card49.type = CardType::item;

	MunchkinCard card50;
	card50.markerID = 50;
	card50.cardName = "Untot für Monster";
	card50.type = CardType::joker;

	MunchkinCard card51;
	card51.markerID = 51;
	card51.cardName = "Untot für Monster2";
	card51.type = CardType::joker;

	MunchkinCard card52;
	card52.markerID = 52;
	card52.cardName = "Waldschrat";
	card52.type = CardType::monster;

	MunchkinCard card53;
	card53.markerID = 53;
	card53.cardName = "Walhalla erreichen";
	card53.type = CardType::lvlUp;

	MunchkinCard card54;
	card54.markerID = 54;
	card54.cardName = "Wikingerente";
	card54.type = CardType::curse;

	MunchkinCard card55;
	card55.markerID = 55;
	card55.cardName = "Wunschring4";
	card55.type = CardType::item;

	MunchkinCard card56;
	card56.markerID = 56;
	card56.cardName = "Wunschring3";
	card56.type = CardType::item;

	MunchkinCard card57;
	card57.markerID = 57;
	card57.cardName = "Wunschring2";
	card57.type = CardType::item;

	MunchkinCard card58;
	card58.markerID = 58;
	card58.cardName = "Wurfnetz";
	card58.type = CardType::item;

	MunchkinCard card59;
	card59.markerID = 59;
	card59.cardName = "Zahnkrone";
	card59.type = CardType::item;

	MunchkinCard card60;
	card60.markerID = 60;
	card60.cardName = "Bürste des Todes";
	card60.type = CardType::item;

	MunchkinCard card61;
	card61.markerID = 61;
	card61.cardName = "Das war doch genau hier";
	card61.type = CardType::curse;

	MunchkinCard card62;
	card62.markerID = 62;
	card62.cardName = "Den Fährmann bezahlen";
	card62.type = CardType::curse;

	MunchkinCard card63;
	card63.markerID = 63;
	card63.cardName = "Der grosse böse Wolf";
	card63.type = CardType::monster;

	MunchkinCard card64;
	card64.markerID = 64;
	card64.cardName = "Die Schau stehlen";
	card64.type = CardType::joker;

	MunchkinCard card65;
	card65.markerID = 65;
	card65.cardName = "Donnerkeil";
	card65.type = CardType::item;

	MunchkinCard card66;
	card66.markerID = 66;
	card66.cardName = "Du bist nicht würdig";
	card66.type = CardType::curse;

	MunchkinCard card67;
	card67.markerID = 67;
	card67.cardName = "Heldensandwich";
	card67.type = CardType::item;

	MunchkinCard card68;
	card68.markerID = 68;
	card68.cardName = "Toto";
	card68.type = CardType::item;

	MunchkinCard card69;
	card69.markerID = 69;
	card69.cardName = "Zerberus";
	card69.type = CardType::monster;

	cards.push_back(std::move(card0));
	cards.push_back(std::move(card1));
	cards.push_back(std::move(card2));
	cards.push_back(std::move(card3));
	cards.push_back(std::move(card4));
	cards.push_back(std::move(card5));
	cards.push_back(std::move(card6));
	cards.push_back(std::move(card7));
	cards.push_back(std::move(card8));
	cards.push_back(std::move(card9));
	cards.push_back(std::move(card10));
	cards.push_back(std::move(card11));
	cards.push_back(std::move(card12));
	cards.push_back(std::move(card13));
	cards.push_back(std::move(card14));
	cards.push_back(std::move(card15));
	cards.push_back(std::move(card16));
	cards.push_back(std::move(card17));
	cards.push_back(std::move(card18));
	cards.push_back(std::move(card19));
	cards.push_back(std::move(card20));
	cards.push_back(std::move(card21));
	cards.push_back(std::move(card22));
	cards.push_back(std::move(card23));
	cards.push_back(std::move(card24));
	cards.push_back(std::move(card25));
	cards.push_back(std::move(card26));
	cards.push_back(std::move(card27));
	cards.push_back(std::move(card28));
	cards.push_back(std::move(card29));
	cards.push_back(std::move(card30));
	cards.push_back(std::move(card31));
	cards.push_back(std::move(card32));
	cards.push_back(std::move(card33));
	cards.push_back(std::move(card34));
	cards.push_back(std::move(card35));
	cards.push_back(std::move(card36));
	cards.push_back(std::move(card37));
	cards.push_back(std::move(card38));
	cards.push_back(std::move(card39));
	cards.push_back(std::move(card40));
	cards.push_back(std::move(card41));
	cards.push_back(std::move(card42));
	cards.push_back(std::move(card43));
	cards.push_back(std::move(card44));
	cards.push_back(std::move(card45));
	cards.push_back(std::move(card46));
	cards.push_back(std::move(card47));
	cards.push_back(std::move(card48));
	cards.push_back(std::move(card49));
	cards.push_back(std::move(card50));
	cards.push_back(std::move(card51));
	cards.push_back(std::move(card52));
	cards.push_back(std::move(card53));
	cards.push_back(std::move(card54));
	cards.push_back(std::move(card55));
	cards.push_back(std::move(card56));
	cards.push_back(std::move(card57));
	cards.push_back(std::move(card58));
	cards.push_back(std::move(card59));
	cards.push_back(std::move(card60));
	cards.push_back(std::move(card61));
	cards.push_back(std::move(card62));
	cards.push_back(std::move(card63));
	cards.push_back(std::move(card64));
	cards.push_back(std::move(card65));
	cards.push_back(std::move(card66));
	cards.push_back(std::move(card67));
	cards.push_back(std::move(card68));
	cards.push_back(std::move(card69));

	return cards;

}