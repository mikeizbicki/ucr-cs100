#/bin/bash

git remote add upstream https://github.com/mikeizbicki/ucr-cs100.git
echo "creating update.sh file..."
touch update.sh
echo "#/bin/bash" > update.sh
echo $'#curtousy of Henry Garcia\n\nclear\necho \"Fetching Update\"\ngit fetch upstream\ngit rebase upstream/cs100-2014fall\necho \"now you will be prompted to push your github repository...\"\ngit push\n ' >> update.sh
chmod 555 update.sh
echo "Done: Update your forked repository with cs100 by typing: ./update.sh"
rm -rf createUpdateScript.sh
