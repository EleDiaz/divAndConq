import           Development.Shake
import           Development.Shake.FilePath
import           Development.Shake.Util
import           System.Console.GetOpt

compiler = "clang++"
cflags   = "-g -std=c++11 -Wall"

hscompiler = "stack ghc"

main :: IO ()
main = shakeArgs shakeOptions{shakeFiles="_build/", shakeVerbosity = Chatty} $ do
    want [ "_build/run" <.> exe
         , "_build/stats" <.> exe
         , "_build/chart" <.> exe
         ]

    phony "clean" $ do
      putNormal "Cleaning files in _build"
      removeFilesAfter "_build" ["//*"]

    phony "chart" $ do
      need ["_build/stats" <.> exe, "_build/chart" <.> exe]
      putNormal "Making chart"
      cmd Shell "./_build/stats > datos && ./_build/chart datos"

    ("_build/chart") <.> exe %> \out -> do
      putNormal ("Compiling" ++ out)
      cs <- getDirectoryFiles "." ["chart.hs"]
      cmd hscompiler cs "-- -o" [out]

    makeBuildMacro "demo" "DEMO"
    makeBuildMacro "run" "RUN"
    makeBuildMacro "stats" "STATS"

-- makeBuildMacro :: String -> String -> UPS
makeBuildMacro exec macro = do
    phony exec $ do
      need ["_build/" ++ exec]
      putNormal ("Executing..." ++ exec)
      cmd ("./_build/" ++ exec)

    ("_build/" ++ exec) <.> exe %> \out -> do
      cs <- getDirectoryFiles "src" ["//*.cpp"]
      let os = ["_build" </> c -<.> ("o"++macro) | c <- cs]
      need os
      cmd compiler cflags ("-D" ++ macro) "-o" [out] os

    ("_build//*.o" ++ macro) %> \out -> do
      let c = "src" </> dropDirectory1 out -<.> "cpp"
      let m = out -<.> "m"
      () <- cmd compiler cflags "-c" [c] ("-D" ++ macro) "-o" [out] "-MMD -MF" [m]
      needMakefileDependencies m
