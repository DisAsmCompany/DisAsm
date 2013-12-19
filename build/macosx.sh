#!/bin/sh
rm -rf macosx
mkdir macosx
cp CMakeLists.txt macosx/CMakeLists.txt
cd macosx
cmake -G "Xcode"
xcodebuild -configuration Debug
xcodebuild -configuration Release
Release/DisAsmTest
cd ..
