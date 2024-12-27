
# Build Game
all:
	$(MAKE) -C src

# Run tests
test:
	$(MAKE) -C src test

# Clean build artifacts
clean:
	$(MAKE) -C src clean