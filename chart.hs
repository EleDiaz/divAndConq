import System.Environment

import Text.Parsec
import Text.Parsec.Char
import Text.Parsec.ByteString

import Graphics.Rendering.Chart.Easy
import Graphics.Rendering.Chart.Backend.Cairo

data DataPlot = DataPlot
            { title :: String
            , listPoints :: [(String,[(Int,Int,Int,Int)])]
            } deriving (Show, Eq)

parsePlot = do
  title <- words
  newline
  listPoints <- many1 $ do
    plotname <- words
    newline
    points <- many1 $ do
      size <- int
      space
      min  <- int
      space
      med  <- int
      space
      max  <- int
      newline
      return (size, min, med, max)
    return (plotname, points)
  return $ DataPlot title listPoints

  where
    words = concat <$> many1 (many1 alphaNum <|> string "ñ" <|> (many1 $ char ' '))
    int   = read <$> many1 digit

errbars :: String -> [(Int,Int,Int,Int)] -> EC l2 (PlotErrBars Int Int)
errbars title vals = liftEC $ do
  c <- takeColor
  plot_errbars_values .= [asymetricErrPoint size med min max | (size,min,med,max) <- vals]
  plot_errbars_title .= "Rango max y min"
  plot_errbars_line_style . line_color .= c

  where
    asymetricErrPoint x y min max = ErrPoint (ErrValue (x) x (x)) (ErrValue min y max)

main :: IO ()
main = do
  (file:_) <- getArgs
  eitherDPlot <- parseFromFile parsePlot file
  case eitherDPlot of
   Left err -> print err
   Right dPlot -> do
     toFile (FileOptions (800, 600) SVG) (title dPlot ++ ".svg") $ do
       setColors (map opaque [blue, red])
       layout_title .= title dPlot
       mapM_ (plot . uncurry errbars) (listPoints dPlot)
       mapM_ (plot . uncurry points . (\(name, points) -> (name, [(x,y) | (x,_,y,_) <- points]))) (listPoints dPlot)
       mapM_ (plot . uncurry line . (\(name, points) -> (name, [[(x,y) | (x,_,y,_) <- points]]))) (listPoints dPlot)



-- main :: IO ()
-- main = do
--   (file:_) <- getArgs
--   eitherDPlot <- parseFromFile parsePlot file
--   case eitherDPlot of
--    Left err -> print err
--    Right dPlot -> do
--      toFile (FileOptions (800, 600) SVG) (title dPlot ++ ".svg") $ do
--        setColors (map opaque [blue, red])
--        layout_title .= title dPlot
--        mapM_ (plot . uncurry errbars) (listPoints dPlot)
--        mapM_ (plot . uncurry points . (\(name, points) -> (name, [(x,y) | (x,_,y,_) <- points]))) (listPoints dPlot)

