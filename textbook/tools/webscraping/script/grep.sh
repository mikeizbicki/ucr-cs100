# sh grep.sh [path/file] [output]
grep -r '<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name">.*</h1>\|<span id="lblIngAmount" class="ingredient-amount">.*</span>\|<span id="lblIngName" class="ingredient-name">.*</span>\|<span class="plaincharacterwrap break">.*</span>' $1 | cat > $2
