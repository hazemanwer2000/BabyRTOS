
# Write README.md for Doxygen.
cat readme_a.md > ../README.md
cat readme_z.md >> ../README.md

# Generate documentation.
doxygen dconfig
cp ../docs/.nojekyll ../html
rm -rf ../docs
mv ../html ../docs

# Write README.md for GitHub.
cat readme_b.md > ../README.md
cat readme_z.md >> ../README.md

# ...
read -p "Done."