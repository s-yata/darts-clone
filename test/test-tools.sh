#! /bin/sh

tool_dir="../src"
mkdarts_path="${tool_dir}/mkdarts"
darts_path="${tool_dir}/darts"

"${mkdarts_path}" test-lexicon test-dic
if [ $? -ne 0 ]
then
  echo "Error: ${mkdarts_path} failed"
  exit 1
fi

cmp test-dic correct-dic
if [ $? -ne 0 ]
then
  echo "Error: incorrect dictionary"
  exit 1
fi

echo "Done! ${mkdarts_path}"
  
"${darts_path}" test-dic < test-text > test-result
if [ $? -ne 0 ]
then
  echo "Error: ${darts_path} failed"
  exit 1
fi

cat correct-result | cmp test-result
if [ $? -ne 0 ]
then
  echo "Error: incorrect result"
  exit 1
fi

echo "Done! ${darts_path}"
