using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Card_Sim.Classes;
using System.Collections.Generic;

namespace Card_Sim
{
    public class Game1 : Game
    {
        private GraphicsDeviceManager _graphics;
        private SpriteBatch _spriteBatch;



        Texture2D logoTexture, buttonTexture;

        Button gameButton, goToMenuButton;

        private WhistGame Whist;





        

        int displayWidth, displayHeight;

        enum GameState
        {
            main_menu, settings, whist
        }

        private GameState _gameState = GameState.main_menu;
        private bool changing = false;



        public Game1()
        {
            _graphics = new GraphicsDeviceManager(this);

            Content.RootDirectory = "Content";
            IsMouseVisible = true;
        }

        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            _graphics.PreferredBackBufferWidth = GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Width;
            _graphics.PreferredBackBufferHeight = GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Height;
            displayWidth = GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Width;
            displayHeight = GraphicsAdapter.DefaultAdapter.CurrentDisplayMode.Height;
            _graphics.IsFullScreen = true;

            _graphics.ApplyChanges();





            base.Initialize();
        }

        protected override void LoadContent()
        {
            _spriteBatch = new SpriteBatch(GraphicsDevice);

            // TODO: use this.Content to load your game content here
            logoTexture = Content.Load<Texture2D>("logo_sketch_1");
            buttonTexture = Content.Load<Texture2D>("button");


            Whist = new WhistGame(_spriteBatch, Content);


        
            gameButton = new Button(buttonTexture, 0, 0);
            gameButton.MoveTo((displayWidth - gameButton.width) / 2, (displayHeight - gameButton.height) / 2);
            goToMenuButton = new Button(buttonTexture, 0, 0, 1f);
            goToMenuButton.ChangeBaseSize(100);
            goToMenuButton.MoveTo(0, 0);


            
            /*
            deck.MoveTo(Card.Name.aceOfHearts, playerHand);
            deck.MoveTo(Card.Name.kingOfHearts, playerHand);
            deck.MoveTo(Card.Name.queenOfHearts, playerHand);
            deck.MoveTo(Card.Name.jackOfHearts, playerHand);
            deck.MoveTo(Card.Name.tenOfHearts, playerHand);
            deck.MoveTo(Card.Name.nineOfHearts, playerHand);
            deck.MoveTo(Card.Name.eightOfHearts, playerHand);
            deck.MoveTo(Card.Name.sevenOfHearts, playerHand);
            */

        }

        protected override void Update(GameTime gameTime)
        {

            if (Mouse.GetState().LeftButton != ButtonState.Pressed && !Keyboard.GetState().IsKeyDown(Keys.Escape) 
                && !Keyboard.GetState().IsKeyDown(Keys.Escape) && changing == true)
            {
                changing = false;
            }

            if ((GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                    && _gameState == GameState.main_menu && changing == false)
            {
                Exit();
            }


            // TODO: Add your update logic here
            if (_gameState == GameState.main_menu )
            {
                gameButton.Update();
                if ((gameButton.Pressed() || Keyboard.GetState().IsKeyDown(Keys.Enter)) && !changing)
                {
                    _gameState = GameState.whist;
                    changing = true;

                }
            }
            if (_gameState == GameState.whist)
            {
                if (changing == false)
                {
                    Whist.Update();
                    goToMenuButton.Update();

                    if ((goToMenuButton.Pressed() || Keyboard.GetState().IsKeyDown(Keys.Escape)) && !changing)
                    {
                        _gameState = GameState.main_menu;
                        changing = true;

                    }
                }

            }

            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.ForestGreen);

            // TODO: Add your drawing code here
            if(_gameState == GameState.main_menu)
            {
                _spriteBatch.Begin();

                _spriteBatch.Draw(logoTexture, new Rectangle(0, 0, 1920, 1080), Color.White);
                _spriteBatch.Draw(gameButton.texture, new Rectangle(gameButton.X, gameButton.Y, gameButton.width, gameButton.height), Color.White);
                _spriteBatch.End();
            };
            if (_gameState == GameState.whist)
            {
                _spriteBatch.Begin();

                _spriteBatch.Draw(goToMenuButton.texture, new Rectangle(goToMenuButton.X, goToMenuButton.Y, goToMenuButton.width, goToMenuButton.height), Color.White);
                Whist.Draw();

                _spriteBatch.End();
            }

            base.Draw(gameTime);
        }
    }
}
