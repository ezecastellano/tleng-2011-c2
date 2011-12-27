#!/bin/sh
rm *.png
for x in $(ls dots); 
do 
	dot "dots/$x" -Tpng -o  "${x%.*}.png";
done
rm dots/*
