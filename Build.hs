import           Development.Shake
import           Development.Shake.FilePath
import           Development.Shake.Util
import           System.Console.GetOpt

flags :: [OptDescr (Either String Bool)]
flags = [Option "" ["debugger"] (NoArg $ Right $ True) "Set -DDEBUG in compiler"]

main :: IO ()
main = shakeArgsWith shakeOptions{shakeFiles="_build/"} flags $ \debug target -> return $ Just $ do

    let debug' = case debug of
                  [] -> False
                  x:_ -> x

    want ["_build/run" <.> exe]

    phony "clean" $ do
      putNormal "Cleaning files in _build"
      removeFilesAfter "_build" ["//*"]

    phony "run" $ do
      need ["_build/run"]
      putNormal "Executing..."
      cmd "./_build/run"

    "_build/run" <.> exe %> \out -> do
      cs <- getDirectoryFiles "src" ["//*.cpp"]
      let os = ["_build" </> c -<.> "o" | c <- cs]
      need os
      cmd (if not debug' then "clang++ -g -std=c++11 -o"
           else "clang++ -g -std=c++11 -DDEBUG -o") [out] os

    "_build//*.o" %> \out -> do
      let c = "src" </> dropDirectory1 out -<.> "cpp"
      let m = out -<.> "m"
      () <- cmd (if not debug' then "clang++ -g -std=c++11 -Wall -c"
                 else "clang++ -g -std=c++11 -DDEBUG -Wall -c") [c] "-o" [out] "-MMD -MF" [m]
      needMakefileDependencies m
