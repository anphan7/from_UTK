#! /bin/bash


echo "Start TLS connection"
echo ""
for site in "gmail.com" "twitter.com"  "youtube.com"  "amazon.com"  "linkedin.com"  "facebook.com"  "github.com"  "utk.edu"  "leetcode.com"  "stackoverflow.com"; do
echo ${site}
openssl s_client -connect ${site}:443 &> tls_${site:0:-4}.txt &
done

echo ""
