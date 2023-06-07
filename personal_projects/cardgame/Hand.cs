using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace Card_Sim.Classes
{
    class Hand
    {

        public int width = 1000, height = 300, X = 460, Y = 780;
        protected int cardSize;
        public List<Card> heldCards;
        protected SpriteBatch spriteBatch;
        private Texture2D handAreaTexture;

        public Hand(SpriteBatch spriteBatchIn, Texture2D handAreaTextureIn)
        {
            heldCards = new List<Card>();
            spriteBatch = spriteBatchIn;
            handAreaTexture = handAreaTextureIn;
        }
        public Hand(List<Card> heldCardsIn)
        {
            heldCards = heldCardsIn;
        }

        public void AddCard(Card addedCard)
        {
            heldCards.Add(addedCard);
        }

        public void RemoveCard(Card removedCard)
        {
            heldCards.Remove(removedCard);
            removedCard.ChangeBaseSize(200);
        }

        public virtual void UpdateHand()
        {
            if (Mouse.GetState().LeftButton != ButtonState.Pressed)
            {
                cardSize = (int)((float)width / (float)(heldCards.Count)) * 2;
                if (cardSize > 200)
                {
                    cardSize = 200;
                }
                for (int i = heldCards.Count - 1; i >= 0 ; i--)
                {
                    if (heldCards[i].held == false)
                    {
                        heldCards[i].ChangeBaseSize(cardSize);
                        heldCards[i].X = X + (cardSize / 2 * i);
                        heldCards[i].Y = Y;
                
                    }
                }
            }
                       
        }

        public virtual void UpdateCards()
        {
            for (int i = heldCards.Count-1; i >= 0; i--)
            {
                heldCards[i].Update();
            }
        }

        public virtual void Draw()
        {
            for (int i = 0; i < heldCards.Count; i++)
            {
                spriteBatch.Draw(heldCards[i].texture, new Rectangle(heldCards[i].X, heldCards[i].Y, heldCards[i].width, heldCards[i].height), Color.White);
            }
        }

        public void DrawArea()
        {
            spriteBatch.Draw(handAreaTexture, new Rectangle(X, Y, width, height), Color.White);
        }

    }
}
