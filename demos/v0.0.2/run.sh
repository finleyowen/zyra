DEMO_DIR="./demos/v0.0.2"
DEMO_INFILE="$DEMO_DIR/demo.in.z"
DEMO_OUTFILE="$DEMO_DIR/demo.out.cpp"

# move into the program directory to build it
cd ../..

# build the compiler
make -B

# create the output file
echo "#include <memory>
class MyClass;" > $DEMO_OUTFILE

# run the Zyra compiler
./zc < $DEMO_INFILE > $DEMO_OUTFILE
