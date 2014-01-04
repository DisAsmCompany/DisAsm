#!/bin/sh
rm -rf macosx
mkdir macosx
cd macosx
cmake -G "Xcode" ..
xcodebuild -configuration Debug
xcodebuild -configuration Release
Release/DisAsmTest
cd ..
