#pragma once
#include <vector>
#include <string>
#include <list>
using namespace std;
struct GameStatus;
struct ATile;
struct Player;
struct Block;

#include "Board.h"

struct PlaceATileOrder;
struct SellStockOrder;
struct HoldStockOrder;
struct ConvertStockOrder;
struct BuyStockOrder;
struct SetupCompanyOrder;

struct PlayerAI{
	const Player* pplayer;
	string id;
	bool ready;
	virtual const string getID(){ return id;}
	//AI cannot change PLAYER status
	virtual void setPlayer( const Player* p ){ pplayer = p; }
	virtual const ConvertStockOrder decideDoStockConversion(const GameStatus& bs )=0;
	virtual const PlaceATileOrder decidePlaceATile( const GameStatus& bs )=0;
	virtual const BuyStockOrder decideBuyStocks( const GameStatus& bs)=0;
	virtual const SellStockOrder decideSellStock( const GameStatus& bs)=0;
	virtual const SetupCompanyOrder decideSetupCompany( const GameStatus& bs )=0;

	virtual void askPlayerToPlaceTile(){ ready= true; }
	virtual void askPlayerToBuyStock(){ ready= true; }
	virtual void askPlayerToSetupCompany(){ ready= true; }
	virtual void askPlayerToSellStock(){ ready= true; }
	virtual void askPlayerToConvertStock(){ ready= true; }
	
	virtual void fyiPlayerInfos( const vector<string> ids)=0 ;
	virtual void fyiPlayerBuyStockOrder( const string& player, const BuyStockOrder& ods )=0;
	virtual void fyiPlayerConvertStockOrder( const string& player, const ConvertStockOrder& ods )=0;
	virtual void fyiPlayerPlaceATileOrder( const string& player, const PlaceATileOrder& ods )=0;
	virtual void fyiPlayerSellStockOrder( const string& player, const SellStockOrder& ods )=0;
	virtual void fyiPlayerSetupCompanyOrder( const string& player, const SetupCompanyOrder& ods )=0;
};
struct DefaultAI:PlayerAI{
	DefaultAI( string iid ){ id = iid; ready = true; }
	DefaultAI(  ){ ready = true; }
	//const string getID()const;
	//AI cannot change PLAYER status
	const ConvertStockOrder decideDoStockConversion(const GameStatus& bs );
	const PlaceATileOrder decidePlaceATile( const GameStatus& bs );
	const BuyStockOrder decideBuyStocks( const GameStatus& bs);
	const SellStockOrder decideSellStock( const GameStatus& bs);
	const SetupCompanyOrder decideSetupCompany( const GameStatus& bs );
	
	void fyiPlayerInfos( const vector<string> ids){}
	void fyiPlayerBuyStockOrder( const string& player, const BuyStockOrder& ods ){}
	void fyiPlayerConvertStockOrder( const string& player, const ConvertStockOrder& ods ){}
	void fyiPlayerPlaceATileOrder( const string& player, const PlaceATileOrder& ods ){}
	void fyiPlayerSellStockOrder( const string& player, const SellStockOrder& ods ){}
	void fyiPlayerSetupCompanyOrder( const string& player, const SetupCompanyOrder& ods ){}
};
struct ZHENWStockPreferenceComparator {
	Block biggest;
	const GameStatus* pGame;
	//const Block getBiggestBlock() const;
	ZHENWStockPreferenceComparator( const GameStatus& bs );
	bool operator()( const Block& b1, const Block& b2 );
};
struct ZHENWAI:PlayerAI{
	ZHENWAI( string iid ){ id = iid; ready = true; }
	ZHENWAI(  ){ ready = true; }
	
	static int calculateTile2BlockDistance( const ATile& t, const Block& b );
	static int calculateBlock2BlockDistance( const Block& b1, const Block& b2 );
	static bool isTileNext2PlayerBlock( const ATile& t, const GameStatus& bs, const Player& p );
	static bool isTileCreatingNewCompany( const ATile& t, const GameStatus& bs );

	const ConvertStockOrder decideDoStockConversion(const GameStatus& bs );
	const PlaceATileOrder decidePlaceATile( const GameStatus& bs );
	const BuyStockOrder decideBuyStocks( const GameStatus& bs);
	const SellStockOrder decideSellStock( const GameStatus& bs);
	const SetupCompanyOrder decideSetupCompany( const GameStatus& bs );
	
	void fyiPlayerInfos( const vector<string> ids){}
	void fyiPlayerBuyStockOrder( const string& player, const BuyStockOrder& ods ){}
	void fyiPlayerConvertStockOrder( const string& player, const ConvertStockOrder& ods ){}
	void fyiPlayerPlaceATileOrder( const string& player, const PlaceATileOrder& ods ){}
	void fyiPlayerSellStockOrder( const string& player, const SellStockOrder& ods ){}
	void fyiPlayerSetupCompanyOrder( const string& player, const SetupCompanyOrder& ods ){}
};


struct HOMAI:DefaultAI{
	HOMAI( string iid ){ id = iid; ready = true; }
	HOMAI(  ){ ready = true; }

	queue<ATile> tile_sequence;
	
	static bool isTilesConnected( const ATile& t1, const ATile& t2 );

	void rearrage_sequence( const GameStatus& status );
	int  lookup_companysize( const GameStatus& bs, COMPANY c );

	const ConvertStockOrder decideDoStockConversion(const GameStatus& bs );
	const PlaceATileOrder decidePlaceATile( const GameStatus& bs );
	const BuyStockOrder decideBuyStocks( const GameStatus& bs);
	const SellStockOrder decideSellStock( const GameStatus& bs);
	const SetupCompanyOrder decideSetupCompany( const GameStatus& bs );
	
	void fyiPlayerInfos( const vector<string> ids){}
	void fyiPlayerBuyStockOrder( const string& player, const BuyStockOrder& ods ){}
	void fyiPlayerConvertStockOrder( const string& player, const ConvertStockOrder& ods ){}
	void fyiPlayerPlaceATileOrder( const string& player, const PlaceATileOrder& ods ){}
	void fyiPlayerSellStockOrder( const string& player, const SellStockOrder& ods ){}
	void fyiPlayerSetupCompanyOrder( const string& player, const SetupCompanyOrder& ods ){}
};

struct AIFactory{
	static PlayerAI* getAI( AITYPE t, const char* name );
};
