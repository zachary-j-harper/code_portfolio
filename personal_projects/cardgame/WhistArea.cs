using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    class WhistArea
    {
        public int width = 400, height = 400, X = 710, Y = 340, playerNumber = 4, turnsTaken, winningHand = 0;
        public List<Card> playedCards;
        public Card.Suit leadSuit = Card.Suit.empty;
        public Card highestCard = null;
        private SpriteBatch spriteBatch;

        public WhistArea(SpriteBatch spriteBatchIn)
        {
            playedCards = new List<Card>();
            spriteBatch = spriteBatchIn;
        }

        public void AddCard(Card addedCard)
        {
            addedCard.X = (1920 - addedCard.width) / 2;
            addedCard.Y = (1080 - addedCard.height) / 2;
            playedCards.Add(addedCard);
            turnsTaken += 1;
            if(leadSuit == Card.Suit.empty)
            {
                leadSuit = addedCard.suit;
            }
            if(highestCard == null)
            {
                highestCard = addedCard;
            }
            else
            {
                if(addedCard.suit == leadSuit && Util.FindHigher(addedCard, highestCard) == addedCard)
                {
                    highestCard = addedCard;
                    winningHand = turnsTaken;
                }
            }
        }

        public void RemoveCard(Card removedCard)
        {
            playedCards.Remove(removedCard);
        }

        public int GetWinner()
        {
            return winningHand;
        }

        public void Draw()
        {
            for (int i = 0; i < playedCards.Count; i++)
            {
                spriteBatch.Draw(playedCards[i].texture, new Rectangle(playedCards[i].X, playedCards[i].Y, playedCards[i].width, playedCards[i].height), Color.White);
            }
        }
    }
}
