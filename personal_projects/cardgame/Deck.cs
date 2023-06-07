using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    class Deck
    {
        public List<Card> allCards;
        public List<Card> containtedCards;

        public Card aceOfHearts, kingOfHearts, queenOfHearts, jackOfHearts, tenOfHearts, nineOfHearts, eightOfHearts, sevenOfHearts,
            sixOfHearts, fiveOfHearts, fourOfHearts, threeOfHearts, twoOfHearts,
            aceOfDiamonds, kingOfDiamonds, queenOfDiamonds, jackOfDiamonds, tenOfDiamonds, nineOfDiamonds, eightOfDiamonds, sevenOfDiamonds,
            sixOfDiamonds, fiveOfDiamonds, fourOfDiamonds, threeOfDiamonds, twoOfDiamonds,
            aceOfSpades, kingOfSpades, queenOfSpades, jackOfSpades, tenOfSpades, nineOfSpades, eightOfSpades, sevenOfSpades, sixOfSpades,
            fiveOfSpades, fourOfSpades, threeOfSpades, twoOfSpades;

        public Deck(ContentManager Content)
        {
            allCards = new List<Card>();
            allCards.Add(aceOfHearts = new Card(Card.Name.aceOfHearts, Content.Load<Texture2D>("ace_of_hearts"), 40, 40));
            allCards.Add(kingOfHearts = new Card(Card.Name.kingOfHearts, Content.Load<Texture2D>("king_of_hearts"), 40, 40));
            allCards.Add(queenOfHearts = new Card(Card.Name.queenOfHearts, Content.Load<Texture2D>("queen_of_hearts"), 40, 40));
            allCards.Add(jackOfHearts = new Card(Card.Name.jackOfHearts, Content.Load<Texture2D>("jack_of_hearts"), 40, 40));
            allCards.Add(tenOfHearts = new Card(Card.Name.tenOfHearts, Content.Load<Texture2D>("ten_of_hearts"), 40, 40));
            allCards.Add(nineOfHearts = new Card(Card.Name.nineOfHearts, Content.Load<Texture2D>("nine_of_hearts"), 40, 40));
            allCards.Add(eightOfHearts = new Card(Card.Name.eightOfHearts, Content.Load<Texture2D>("eight_of_hearts"), 40, 40));
            allCards.Add(sevenOfHearts = new Card(Card.Name.sevenOfHearts, Content.Load<Texture2D>("seven_of_hearts"), 40, 40));
            allCards.Add(sixOfHearts = new Card(Card.Name.sixOfHearts, Content.Load<Texture2D>("six_of_hearts"), 40, 40));
            allCards.Add(fiveOfHearts = new Card(Card.Name.fiveOfHearts, Content.Load<Texture2D>("five_of_hearts"), 40, 40));
            allCards.Add(fourOfHearts = new Card(Card.Name.fourOfHearts, Content.Load<Texture2D>("four_of_hearts"), 40, 40));
            allCards.Add(threeOfHearts = new Card(Card.Name.threeOfHearts, Content.Load<Texture2D>("three_of_hearts"), 40, 40));
            allCards.Add(twoOfHearts = new Card(Card.Name.twoOfHearts, Content.Load<Texture2D>("two_of_hearts"), 40, 40));
            allCards.Add(aceOfDiamonds = new Card(Card.Name.aceOfDiamonds, Content.Load<Texture2D>("ace_of_diamonds"), 40, 40));
            allCards.Add(kingOfDiamonds = new Card(Card.Name.kingOfDiamonds, Content.Load<Texture2D>("king_of_diamonds"), 40, 40));
            allCards.Add(queenOfDiamonds = new Card(Card.Name.queenOfDiamonds, Content.Load<Texture2D>("queen_of_diamonds"), 40, 40));
            allCards.Add(jackOfDiamonds = new Card(Card.Name.jackOfDiamonds, Content.Load<Texture2D>("jack_of_diamonds"), 40, 40));
            allCards.Add(tenOfDiamonds = new Card(Card.Name.tenOfDiamonds, Content.Load<Texture2D>("ten_of_diamonds"), 40, 40));
            allCards.Add(nineOfDiamonds = new Card(Card.Name.nineOfDiamonds, Content.Load<Texture2D>("nine_of_diamonds"), 40, 40));
            allCards.Add(eightOfDiamonds = new Card(Card.Name.eightOfDiamonds, Content.Load<Texture2D>("eight_of_diamonds"), 40, 40));
            allCards.Add(sevenOfDiamonds = new Card(Card.Name.sevenOfDiamonds, Content.Load<Texture2D>("seven_of_diamonds"), 40, 40));
            allCards.Add(sixOfDiamonds = new Card(Card.Name.sixOfDiamonds, Content.Load<Texture2D>("six_of_diamonds"), 40, 40));
            allCards.Add(fiveOfDiamonds = new Card(Card.Name.fiveOfDiamonds, Content.Load<Texture2D>("five_of_diamonds"), 40, 40));
            allCards.Add(fourOfDiamonds = new Card(Card.Name.fourOfDiamonds, Content.Load<Texture2D>("four_of_diamonds"), 40, 40));
            allCards.Add(threeOfDiamonds = new Card(Card.Name.threeOfDiamonds, Content.Load<Texture2D>("three_of_diamonds"), 40, 40));
            allCards.Add(twoOfDiamonds = new Card(Card.Name.twoOfDiamonds, Content.Load<Texture2D>("two_of_diamonds"), 40, 40));
            allCards.Add(aceOfSpades = new Card(Card.Name.aceOfSpades, Content.Load<Texture2D>("ace_of_spades"), 40, 40));
            allCards.Add(kingOfSpades = new Card(Card.Name.kingOfSpades, Content.Load<Texture2D>("king_of_spades"), 40, 40));
            allCards.Add(queenOfSpades = new Card(Card.Name.queenOfSpades, Content.Load<Texture2D>("queen_of_spades"), 40, 40));
            allCards.Add(jackOfSpades = new Card(Card.Name.jackOfSpades, Content.Load<Texture2D>("jack_of_spades"), 40, 40));
            allCards.Add(tenOfSpades = new Card(Card.Name.tenOfSpades, Content.Load<Texture2D>("ten_of_spades"), 40, 40));
            allCards.Add(nineOfSpades = new Card(Card.Name.nineOfSpades, Content.Load<Texture2D>("nine_of_spades"), 40, 40));
            allCards.Add(eightOfSpades = new Card(Card.Name.eightOfSpades, Content.Load<Texture2D>("eight_of_spades"), 40, 40));
            allCards.Add(sevenOfSpades = new Card(Card.Name.sevenOfSpades, Content.Load<Texture2D>("seven_of_spades"), 40, 40));
            allCards.Add(sixOfSpades = new Card(Card.Name.sixOfSpades, Content.Load<Texture2D>("six_of_spades"), 40, 40));
            allCards.Add(fiveOfSpades = new Card(Card.Name.fiveOfSpades, Content.Load<Texture2D>("five_of_spades"), 40, 40));
            allCards.Add(fourOfSpades = new Card(Card.Name.fourOfSpades, Content.Load<Texture2D>("four_of_spades"), 40, 40));
            allCards.Add(threeOfSpades = new Card(Card.Name.threeOfSpades, Content.Load<Texture2D>("three_of_spades"), 40, 40));
            allCards.Add(twoOfSpades = new Card(Card.Name.twoOfSpades, Content.Load<Texture2D>("two_of_spades"), 40, 40));


            for (int i = 0; i < allCards.Count; i++)
            {
                allCards[i].ChangeBaseSize(200);
            }
            containtedCards = allCards;
        }

        public void MoveTo(Card.Name name, Hand playerHand)
        {
            Card foundCard = containtedCards.Find(x => x.name == name);
            playerHand.AddCard(foundCard);
            containtedCards.Remove(foundCard);
        }

        public void MoveFrom(Hand playerHand, Card.Name name)
        {
            Card foundCard = playerHand.heldCards.Find(x => x.name == name);
            playerHand.RemoveCard(foundCard);
            containtedCards.Add(foundCard);
        }

        public void Shuffle(int times)
        {
            while (times > 0)
            {
                times--;
                Card swapper, swappee;
                for (int i = containtedCards.Count - 1; i >= 0; i--)
                {
                    int j = Util.shuffler.Next(i + 1);
                    swappee = containtedCards[j];
                    swapper = containtedCards[i];
                    containtedCards[i] = swappee;
                    containtedCards[j] = swapper;

                }
            }
        }

        public Card Holding()
        {
            return containtedCards.Find(x => x.held == true);
        }

        public void Update()
        {
            for (int i = allCards.Count - 1; i >= 0; i--)
            {
                allCards[i].Update();
            }
        }
    }
}
