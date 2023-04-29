clang -framework CoreAudio -framework CoreFoundation main.c -o switch-audio-device

mv switch-audio-device $HOME/music

echo "alias switch-to-main-device='$HOME/music/switch-audio-device'" >> $HOME/.zshrc

echo "switch-to-main-device" >> $HOME/.zshrc

echo 'osascript -e "set Volume 10"' >> $HOME/.zshrc

echo 'say "I did not lock my screen"' >> $HOME/.zshrc

