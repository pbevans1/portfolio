grep -e "Carbohydrate" ../data/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |sed 's/Carbohydrate, by difference/Carbohydrate/g' |cut -d~ -f1,5|sort>carbs
grep -e "Energy" ../data/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g'|cut -d~ -f1,5|sort >energy
grep -e "Total lipid" ../data/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |sed 's/Total lipid (fat)/Fat/g' |cut -d~ -f1,5|sort>fat
grep -e "Protein" ../data/Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1,5|sort>protein

cat ../data/Products.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1,2,5|sort>product
cat ../data/Serving_size.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1-5|sort>serving

join -t \~ energy carbs>ec
join -t \~ fat protein>fp
join -t \~ ec fp >nutrients
join -t \~ product nutrients >pn
join -t \~ pn serving >../data/food_database.csv