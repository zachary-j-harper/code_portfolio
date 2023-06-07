using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    class CollisionHandler
    {
        public CollisionHandler() { }

        public void PlayerHandDeckCollisions(Deck deck, Hand playerHand)
        {
            for (int i = 0; i < deck.containtedCards.Count; i++)
            {
                if (deck.containtedCards[i].held == false && (deck.containtedCards[i].X + deck.containtedCards[i].width/2) > playerHand.X && (deck.containtedCards[i].X + deck.containtedCards[i].width / 2) < (playerHand.X + playerHand.width)
                    && (deck.containtedCards[i].Y + deck.containtedCards[i].height / 2) > playerHand.Y && (deck.containtedCards[i].Y + deck.containtedCards[i].height / 2) < (playerHand.Y + playerHand.height))
                {
                    Util.MoveCardFromAtoB(deck.containtedCards[i].name, deck, playerHand);
                    

                }
                    
            }
            for (int i = 0; i < playerHand.heldCards.Count; i++)
            {
                if (playerHand.heldCards[i].held == true && (Mouse.GetState().X <= (playerHand.X + 40) || Mouse.GetState().X >= (playerHand.X + playerHand.width - 40)
                    || Mouse.GetState().Y <= (playerHand.Y + 40) || Mouse.GetState().Y <= (playerHand.Y + playerHand.height - 40)))
                {
                    Util.MoveCardFromAtoB(playerHand.heldCards[i].name, playerHand, deck);
                }
            }
        }

        public void Collide(WhistArea Area, Hand playerHand, Deck deck)
        {
            for (int i = 0; i < deck.containtedCards.Count; i++)
            {
                if (deck.containtedCards[i].held == false && (deck.containtedCards[i].X + deck.containtedCards[i].width / 2) > Area.X && (deck.containtedCards[i].X + deck.containtedCards[i].width / 2) < (Area.X + Area.width)
                    && (deck.containtedCards[i].Y + deck.containtedCards[i].height / 2) > Area.Y && (deck.containtedCards[i].Y + deck.containtedCards[i].height / 2) < (Area.Y + Area.height))
                {
                    Util.MoveCardFromAtoB(deck.containtedCards[i].name, deck, Area);


                }

            }
            for (int i = 0; i < playerHand.heldCards.Count; i++)
            {
                if (playerHand.heldCards[i].held == true && (Mouse.GetState().X <= (playerHand.X + 40) || Mouse.GetState().X >= (playerHand.X + playerHand.width - 40)
                    || Mouse.GetState().Y <= (playerHand.Y + 40) || Mouse.GetState().Y <= (playerHand.Y + playerHand.height - 40)))
                {
                    Util.MoveCardFromAtoB(playerHand.heldCards[i].name, playerHand, Area);
                }
            }
        }


        public void CardOrderUpdate(List<Card> cardList)
        {
            Card movingCard;

            for ( int i = 0; i < cardList.Count; i++)
            {
                if (cardList[i].held == true)
                {
                    movingCard = cardList[i];
                    cardList.Remove(movingCard);
                    cardList.Add(movingCard);
                }
            }
        }




    }
}
