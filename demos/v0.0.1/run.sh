DEMO_DIR="./demos/v0.0.1"
DEMO_INFILE="$DEMO_DIR/demo.in.z"
DEMO_OUTFILE="$DEMO_DIR/demo.out.cpp"
DEMO_DIFF_TMP="$DEMO_DIR/diff0.txt"
DEMO_DIFF="$DEMO_DIR/diff.txt"

# move into the program directory to build it
cd ../..

# build the compiler
make -B

# create the output file
echo "#include <memory>
class MyClass;" > $DEMO_OUTFILE

# run the Zyra compiler
./zc < $DEMO_INFILE > $DEMO_OUTFILE

# generate the side-by-side comparison
> $DEMO_DIFF
diff -y -w --width=164 $DEMO_INFILE $DEMO_OUTFILE > $DEMO_DIFF_TMP
expand $DEMO_DIFF_TMP > $DEMO_DIFF

# remove temp file
rm $DEMO_DIFF_TMP