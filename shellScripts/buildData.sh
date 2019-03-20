grep -e "Carbohydrate" dataBuilder/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |sed 's/Carbohydrate, by difference/Carbohydrate/g' |cut -d~ -f1,5|sort>dataBuilder/carbs
grep -e "Energy" dataBuilder/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g'|cut -d~ -f1,5|sort >dataBuilder/energy
grep -e "Total lipid" dataBuilder/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |sed 's/Total lipid (fat)/Fat/g' |cut -d~ -f1,5|sort>dataBuilder/fat
grep -e "Protein" dataBuilder/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1,5|sort>dataBuilder/protein

cat dataBuilder/Products.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1,2,5|sort>dataBuilder/product
cat dataBuilder/Serving_size.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1-5|sort>dataBuilder/serving

join -t \~ dataBuilder/energy dataBuilder/carbs>dataBuilder/ec
join -t \~ dataBuilder/fat dataBuilder/protein>dataBuilder/fp
join -t \~ dataBuilder/ec dataBuilder/fp >dataBuilder/nutrients
join -t \~ dataBuilder/product dataBuilder/nutrients >dataBuilder/pn
join -t \~ dataBuilder/pn dataBuilder/serving >data/food_database.csv