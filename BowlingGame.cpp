#include <iostream>
#include <vector>
using namespace std;
enum ReturnCode
{
    E_NOIMPLEMENTATION =-2,
    SUCESS =0,
    FAILURE =-1
};
class Frame {
	int mFirstRoll;
	int mSecondRoll;
	int mNextFirstRoll;
	int mNextSecondRoll;
	int mExtraRoll;
	bool mSpare;
	bool mStrike;
	int mPoints;
public:
	void isSpare(bool spare)
	{
		mSpare=spare;
	}
	void isStrike(bool strike)
	{
		mStrike=strike;
	}
	void firstRoll(int firstroll)
	{
		mFirstRoll=firstroll;
	}
	void secondRoll(int secondroll)
	{
		mSecondRoll=secondroll;
	}
	void extraRoll(int extraroll)
	{
		mExtraRoll=extraroll;
	}
	void nextFirstRoll(int nextfirstroll)
	{
		mNextFirstRoll=nextfirstroll;
	}
	void nextSecondRoll(int nextsecondroll)
	{
		mNextSecondRoll=nextsecondroll;
	}
	void pointsCurrentFrame(int points)
	{
		mPoints=points;
	}
	int pointsFromFrame()
	{
		if(mExtraRoll > 0)
		{
			return mPoints+mExtraRoll;
		}
		else
		{
			return mPoints;
		}
	}
};
class IGame {
public:
	virtual int insertFrame(Frame  *frame)=0;
	virtual int displayFrame()=0;
	virtual int totalScore()=0;
};
class Game : public IGame
{
public:
	int insertFrame(Frame  *frame)
	{
        return ReturnCode::E_NOIMPLEMENTATION;
	}
	int displayFrame()
	{
        return ReturnCode::E_NOIMPLEMENTATION;
	}
	int totalScore()
	{
        return ReturnCode::E_NOIMPLEMENTATION;
	}
};
class Bowling : public Game {
	int nFrame;
	int mTotalScore;
	std::vector<Frame*> mFrameStore;
public:
	Bowling():mTotalScore(0)
	{
	}
	~Bowling()
	{
	}
	int totalScore()
	{
		for(auto var:mFrameStore)
		{
			mTotalScore=mTotalScore+var->pointsFromFrame();
		}
		return  mTotalScore;
	}
	int insertFrame(Frame  *frame)
	{
		mFrameStore.push_back(frame);
		return ReturnCode::SUCESS;
	}
};
class IGameManager {
    public:
	virtual int executeGame(std::vector<int> &rolls)=0;
	virtual int showScore()=0;
};
class GameManager : public IGameManager
{
	Frame *mFrame;
	Game *mBowling;
	int mFrameCounter;
public:
	GameManager():mFrame(nullptr),mBowling(nullptr),mFrameCounter(0)
	{

	}
	int executeGame(std::vector<int> &rolls)
	{
		int first = rolls[0];
		int second = rolls[1];
		int bonus = 0;
		int i=2;
		mBowling = new Bowling();
		while(i < rolls.size())
		{
			mFrame = new Frame();
			if((first == 10))
			{
				//Strike
				i=i-1;
				bonus = rolls[i] + rolls[i+1];
				first=rolls[i];
				second=rolls[i+1];
				mFrame->isStrike(true);
				mFrame->isSpare(false);
				mFrame->firstRoll(first);
				mFrame->secondRoll(second);
				mFrame->extraRoll(-1);
				mFrame->nextFirstRoll(rolls[i]);
				mFrame->nextSecondRoll(rolls[i+1]);
				mFrame->pointsCurrentFrame(first+bonus);
				mBowling->insertFrame(mFrame);
				i=i+2;
				mFrameCounter++;
			}
			else if((first + second == 10))
			{
				//Spare
				bonus = rolls[i];
				first = rolls[i];
				second = rolls[i+1];
				mFrame->isStrike(false);
				mFrame->isSpare(true);
				mFrame->firstRoll(first);
				mFrame->secondRoll(second);
				if(mFrameCounter == 9)
				{
					mFrame->extraRoll(rolls[i]);
				}
				else
				{
					mFrame->extraRoll(-1);
				}
				mFrame->nextFirstRoll(rolls[i]);
				mFrame->nextSecondRoll(rolls[i+1]);
				mFrame->pointsCurrentFrame(first +second + bonus);
				mBowling->insertFrame(mFrame);
				i=i+2;
				mFrameCounter++;
			}
			else if((first + second < 10))
			{
				first = rolls[i];
				second = rolls[i+1];
				mFrame->isStrike(false);
				mFrame->isSpare(false);
				mFrame->firstRoll(first);
				mFrame->secondRoll(second);
				mFrame->extraRoll(-1);
				mFrame->nextFirstRoll(rolls[i]);
				mFrame->nextSecondRoll(rolls[i+1]);
				mFrame->pointsCurrentFrame(first +second);
				mBowling->insertFrame(mFrame);
				i=i+2;
				mFrameCounter++;
			}
		}//end  while
		
	    return ReturnCode::SUCESS;
	}
	int showScore()
	{
	   std::cout<<"Total Score  "<<mBowling->totalScore()<<"\n";
	   return ReturnCode::SUCESS;
	}
};
int main()
{
	vector<int> roll{1,4,4,5,6,4,5,5,10,0,1,7,3,6,4,10,2,8,6};
	//vector<int> roll{10,10,10,10,10,10,10,10,10,10,10,10};
IGameManager *game = new GameManager();
game->executeGame(roll);
game->showScore();
	return 0;
}
