#!
rm -f web.tar.gz
tar zcvf web.tar.gz --exclude *.bak --exclude 'cgi-bin/*' --exclude comp* *
