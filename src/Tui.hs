{-# LANGUAGE OverloadedStrings #-}

module Tui where

import Brick.AttrMap
import Brick.Main
import Brick.Types
import Brick.Util
import Brick.Widgets.Core
import Brick.Widgets.Border 
import Control.Monad
import Control.Monad.IO.Class
import Cursor.Simple.List.NonEmpty
import Data.List (sort)
import Data.List.NonEmpty (NonEmpty (..), nonEmpty)
import qualified Data.List.NonEmpty as NE
import Graphics.Vty.Attributes
import Graphics.Vty.Input.Events
import System.Exit
import System.Directory (doesFileExist, getCurrentDirectory, getDirectoryContents, setCurrentDirectory, doesDirectoryExist)

tui :: IO ()
tui = do
  initialState <- buildInitialState
  endState <- defaultMain tuiApp initialState
  print endState

data TuiState = TuiState
  { tuiStatePaths :: NonEmptyCursor DirectoryEntry
  }
  deriving (Show, Eq)

data DirectoryEntry
  = File FilePath 
  | Directory FilePath 
  deriving (Show, Eq, Ord)

type ResourceName = String 

{-

data ResourceName = Viewport1
let w = viewport Viewport1 Horizontal $ 
        (visible $ str "Hello,") <+> (str "World!")
-}

tuiApp :: App TuiState e ResourceName
tuiApp =
  App
    { appDraw = drawTui,
      appChooseCursor = showFirstCursor,
      appHandleEvent = handleTuiEvent,
      appStartEvent = pure,
      appAttrMap = const $ attrMap mempty
                                   [
                                      ("selected", bg white)
                                    , ("file", fg green)
                                    , ("directory",fg blue)
                                   ]
    }

buildInitialState :: IO TuiState
buildInitialState = do
  here <- getCurrentDirectory
  contents <-  getDirectoryContents here
  contents' <- forM (sort contents) $ \fp -> do
    c <- doesFileExist fp
    if c then pure $ File fp else pure $ Directory fp 
  case NE.nonEmpty $ contents' of
    Nothing -> die "There are no contents."
    Just ne ->
      pure TuiState {tuiStatePaths = makeNonEmptyCursor ne}


-- vBox :: [Widget n] -> Widget n
drawTui :: TuiState -> [Widget ResourceName]
drawTui ts =
  let nec = tuiStatePaths ts
   in [ border $
        vBox   $
        concat
            [ map (drawPath False) $ reverse $ nonEmptyCursorPrev nec
            , [drawPath True $ nonEmptyCursorCurrent nec]
            , map (drawPath False) $ nonEmptyCursorNext nec
            ]
      ]

-- str :: String -> Widget n
drawPath :: Bool -> DirectoryEntry -> Widget n
drawPath b dirent =
  ( if b
      then forceAttr "selected"
      else id ) $ case dirent of 
        File fp -> withAttr "file" $ str fp
        Directory fp -> withAttr "directory" $ str fp 

handleTuiEvent :: TuiState -> BrickEvent n e -> EventM n (Next TuiState)
handleTuiEvent s e =
  case e of
    VtyEvent vtye ->
      case vtye of
        EvKey (KChar 'q') [] -> halt s
        EvKey (KChar 'j') [] -> do
          let nec = tuiStatePaths s
          case nonEmptyCursorSelectNext nec of
            Nothing -> continue s
            Just nec' -> continue $ s {tuiStatePaths = nec'}
        EvKey (KChar 'k') [] -> do
          let nec = tuiStatePaths s
          case nonEmptyCursorSelectPrev nec of
            Nothing -> continue s
            Just nec' -> continue $ s {tuiStatePaths = nec'}
        EvKey (KChar 'o') [] -> do 
          let fp = nonEmptyCursorCurrent $ tuiStatePaths s 
          case fp of 
            File _ -> continue s 
            Directory fp -> do 
              liftIO $ setCurrentDirectory fp
              s' <- liftIO buildInitialState 
              continue s'
        _ -> continue s
    _ -> continue s
