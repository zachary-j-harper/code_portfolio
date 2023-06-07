using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    public class Button : Item
    {
        public Button(Texture2D textureIn, int xIn, int yIn) : base(textureIn, xIn, yIn)
        {

        }

        public Button(Texture2D textureIn, int xIn, int yIn, float rationIn) : base(textureIn, xIn, yIn, rationIn)
        {

        }

        public bool Pressed()
        {
            if (Mouse.GetState().X > X && Mouse.GetState().X < (X + width)
                    && Mouse.GetState().Y > Y && Mouse.GetState().Y < (Y + height) && Mouse.GetState().LeftButton == ButtonState.Pressed)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
