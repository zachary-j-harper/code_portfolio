using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    public class Item
    {
        public Texture2D texture;
        protected float ratio;
        public int width;
        protected int baseWidth, selectedWidth;
        public int height;
        public int X, Y;


        public Item(Texture2D textureIn, int xIn, int yIn)
        {


            texture = textureIn;
            width = textureIn.Width;
            baseWidth = textureIn.Width;
            height = textureIn.Height;
            ratio = (float)height / (float)width;
            X = xIn;
            Y = yIn;

        }

        public Item(Texture2D textureIn, int xIn, int yIn, float ratioIn)
        {

            texture = textureIn;
            width = textureIn.Width;
            baseWidth = textureIn.Width;
            height = textureIn.Height;
            ratio = ratioIn;
            X = xIn;
            Y = yIn;

        }

        public void ChangeSize(int widthTo)
        {

            X -= (widthTo - width) / 2;
            Y -= ((int)(ratio * widthTo) - height) / 2;
            width = widthTo;
            height = (int)((float)ratio * (float)widthTo);

        }

        public void ChangeBaseSize(int widthTo)
        {

            X -= (widthTo - width) / 2;
            Y -= ((int)(ratio * widthTo) - height) / 2;
            baseWidth = widthTo;
            width = widthTo;
            height = (int)((float)ratio * (float)widthTo);

        }

        public void MoveTo(int xIn, int yIn)
        {
            X = xIn; Y = yIn;
        }


        public virtual void Update()
        {

            if (Mouse.GetState().X > X && Mouse.GetState().X < (X + width)
                    && Mouse.GetState().Y > Y && Mouse.GetState().Y < (Y + height))
            {
                ChangeSize((int)(baseWidth*1.1));
            }
            else
            {
                ChangeSize(baseWidth);
            }
        }
    }
}
