using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    public class Card : Item
    {
        public bool held = false;
        public enum Name
        {
            empty,
            aceOfClubs,
            kingOfClubs,
            queenOfClubs,
            jackOfClubs,
            tenOfClubs,
            nineOfClubs,
            eightOfClubs,
            sevenOfClubs,
            sixOfClubs,
            fiveOfClubs,
            fourOfClubs,
            threeOfClubs,
            twoOfClubs,
            aceOfDiamonds,
            kingOfDiamonds,
            queenOfDiamonds,
            jackOfDiamonds,
            tenOfDiamonds,
            nineOfDiamonds,
            eightOfDiamonds,
            sevenOfDiamonds,
            sixOfDiamonds,
            fiveOfDiamonds,
            fourOfDiamonds,
            threeOfDiamonds,
            twoOfDiamonds,
            aceOfHearts,
            kingOfHearts,
            queenOfHearts,
            jackOfHearts,
            tenOfHearts,
            nineOfHearts,
            eightOfHearts,
            sevenOfHearts,
            sixOfHearts,
            fiveOfHearts,
            fourOfHearts,
            threeOfHearts,
            twoOfHearts,
            aceOfSpades,
            kingOfSpades,
            queenOfSpades,
            jackOfSpades,
            tenOfSpades,
            nineOfSpades,
            eightOfSpades,
            sevenOfSpades,
            sixOfSpades,
            fiveOfSpades,
            fourOfSpades,
            threeOfSpades,
            twoOfSpades
        }
        public enum Suit
        {
            Club,
            Diamond,
            Heart,
            Spade,
            empty
        }
        public enum Value
        {
            ace,
            king,
            queen,
            jack,
            ten,
            nine,
            eight,
            seven,
            six,
            five,
            four,
            three,
            two,
            empty
        }
        public Name name;
        public Value value;
        public Suit suit;

        public Card(Name nameIn, Texture2D textureIn, int xIn, int yIn) : base(textureIn, xIn, yIn)
        {
            name = nameIn;

            
        }
        public override void Update()
        {

            if (Mouse.GetState().X > X && Mouse.GetState().X < (X + width)
                    && Mouse.GetState().Y > Y && Mouse.GetState().Y < (Y + height))
            {
                ChangeSize((int)(baseWidth*1.1));
                if (Mouse.GetState().LeftButton == ButtonState.Pressed && (Util.HeldCard == Name.empty || Util.HeldCard == name ) )
                {
                    X = Mouse.GetState().X - width / 2;
                    Y = Mouse.GetState().Y - height / 2;
                    held = true;
                    Util.holdingCard = true;
                    Util.HeldCard = name;
                }
                else
                {
                    if (Mouse.GetState().LeftButton != ButtonState.Pressed && Util.HeldCard == name)
                    {
                        held = false;
                        Util.holdingCard = false;
                        Util.HeldCard = Name.empty;
                    }

                }
            }
            else
            {
                ChangeSize(baseWidth);
                held = false;
            }
        }

        public void UpdateUnclickable()
        {
            ChangeSize(baseWidth);
            held = false;
        }

    }
}
