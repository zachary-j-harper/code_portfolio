using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Card_Sim.Classes
{
    class Trick : Item
    {
        public List<Card> wonCards;

        public Trick(Texture2D textureIn, int xIn, int yIn) : base(textureIn, xIn, yIn)
        {

        }

    }
}
