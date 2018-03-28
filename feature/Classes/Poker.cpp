#include "Poker.h"
#include "GameScene.h"



Poker::Poker()
{}


Poker::~Poker()
{}

Poker * Poker::create(const char * fileName, const Rect rect)
{
			Poker *poke = new Poker;
			if (poke && poke->initWithFile(fileName,rect))
			{
						poke->retain();
						return poke;
			}
			CC_SAFE_DELETE(poke);
			return nullptr;
}

bool Poker::initWithFile(const char * fileName, const Rect rect)
{
			bool isRet = false;
			do
			{
						Sprite::initWithFile(fileName, rect);
						setSelectedPk(false);
						setCanSelectdPk(false);
						setUsed(true);
						isRet = true;
			} while (0);
			return isRet = isRet;
}

void Poker::setReverse()
{
			this->setTextureRect(Rect(numberReverse*pkWidth, suitReverse*pkHeight, pkWidth, pkHeight));
}

void Poker::showCards()
{
			if (m_suit == Joker)
			{
						this->setTextureRect(Rect((m_number- blackJoker)*pkWidth, m_suit*pkHeight, pkWidth, pkHeight));
			}
			else
			{
						this->setTextureRect(Rect(m_number*pkWidth, m_suit*pkHeight, pkWidth, pkHeight));
			}
			
}

void Poker::pkSetPosition(Point pt)
{
			//showCards();
				
			setPosition(pt);
			
}

Poker * Poker::copy()
{
			Poker *newpk = nullptr;
			if (!newpk)
			{
						int suit = this->getSuit();
						int pknumber = this->getpkNumber();
						GameScene *game = this->getGameMain();
						if (suit != Joker)
						{
									newpk = Poker::create(pokerFileName, Rect(pknumber*pkWidth, suit*pkHeight, pkWidth, pkHeight));

						}
						else
						{
									newpk = Poker::create(pokerFileName, Rect((pknumber - blackJoker)*pkWidth, suit*pkHeight, pkWidth, pkHeight));
						}
						newpk->setAnchorPoint(Point(0, 0));
						newpk->setSuit(suit);
						newpk->setpkNumber(pknumber);
						newpk->setGameMain(game);
			}
			return newpk;
}

bool Poker::destroyCard()
{
			bool isRet = false;
			do
			{
						removeFromParent();
						isRet = true;
			} while (0);
			return isRet;
}

void Poker::selectPokerUp()
{
			MoveBy *mvby = MoveBy::create((float)0.2, Point(0, pkHeight / 4));
			this->runAction(mvby);
}

void Poker::selectPokerDown()
{
			MoveBy *mvby = MoveBy::create((float)0.2, Point(0, -pkHeight / 4));
			this->runAction(mvby);
}

void Poker::onEnter()
{
			Sprite::onEnter();
			
			
}

void Poker::onExit()
{
			Sprite::onExit();
			
}


