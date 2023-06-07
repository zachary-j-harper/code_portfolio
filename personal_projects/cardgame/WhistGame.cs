using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    class WhistGame
    {
        public WhistArea Area
        {
            get; set;
        }
        SpriteBatch spriteBatch;
        private CollisionHandler collisionHandler = new CollisionHandler();

        private Deck deck;
        private Card cardBack;

        private Hand playerHand;
        private OpponentHand handLeft, handRight, handTop;
        private Texture2D playAreaTexture, handAreaTexture, cardBackTexture;

        public WhistGame(SpriteBatch spriteBatchIn, ContentManager Content)
        {
            Area = new WhistArea(spriteBatchIn);
            spriteBatch = spriteBatchIn;

            playAreaTexture = Content.Load<Texture2D>("play_mat");
            handAreaTexture = Content.Load<Texture2D>("hand_mat");
            cardBackTexture = Content.Load<Texture2D>("back_two");
            cardBack = new Card(Card.Name.empty, cardBackTexture, 0, 0);


            deck = new Deck(Content);
            deck.Shuffle(5);

            playerHand = new Hand(spriteBatch, playAreaTexture);
            handLeft = new OpponentHand(300, 1000, 1620, 40, cardBack, spriteBatch, playAreaTexture);
            handRight = new OpponentHand(300, 1000, 0, 40, cardBack, spriteBatch, playAreaTexture);
            handTop = new OpponentHand(1000, 300, 460, 0, cardBack, spriteBatch, playAreaTexture);


            Util.Deal(deck, playerHand, handLeft, handRight, handTop, 0);

            playerHand.UpdateHand();
            handLeft.UpdateHand();
            handRight.UpdateHand();
            handTop.UpdateHand();

            playerHand.UpdateCards();
            handLeft.UpdateCards();
            handRight.UpdateCards();
            handTop.UpdateCards();

        }

        public void Update()
        {
            collisionHandler.CardOrderUpdate(deck.containtedCards);
            collisionHandler.Collide(Area, playerHand, deck);
            playerHand.UpdateHand();
            playerHand.UpdateCards();
            deck.Update();
            collisionHandler.PlayerHandDeckCollisions(deck, playerHand);
            if (Area.turnsTaken == Area.playerNumber)
            {
                Area.GetWinner();
            }
        }

        public void Draw()
        {
            spriteBatch.Draw(playAreaTexture, new Rectangle(Area.X, Area.Y, Area.width, Area.height), Color.White);
            playerHand.DrawArea();
            handLeft.DrawArea();
            handRight.DrawArea();
            handTop.DrawArea();
            
            playerHand.Draw();
            handLeft.Draw();
            handRight.Draw();
            handTop.Draw();
            Area.Draw();
            for (int i = 0; i < deck.containtedCards.Count; i++)
            {
                spriteBatch.Draw(deck.containtedCards[i].texture, new Rectangle(deck.containtedCards[i].X, deck.containtedCards[i].Y, deck.containtedCards[i].width, deck.containtedCards[i].height), Color.White);
            }
        }
    }
}
