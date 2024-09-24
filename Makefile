# Définir le compilateur
CC = g++

# Définir les options de compilation avec les optimisations
CFLAGS = -Iinclude -IInclude -Wall -std=c++17

# Options de linkage, ajout des bibliothèques SDL2
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2

# Nom de l'exécutable
TARGET = baller.exe

# Dossier contenant les fichiers sources
SRCDIR = src

# Dossier où les fichiers objets seront stockés
BUILDDIR = build

# Récupérer automatiquement tous les fichiers .cpp dans le dossier src/
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Convertir les fichiers sources .cpp en fichiers objets .o dans le répertoire build/
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Règle par défaut (ce que fait 'make')
all: $(TARGET)

# Créer l'exécutable à partir des fichiers objets, en liant SDL2
$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build completed: $(TARGET)"

# Compiler les fichiers .cpp en fichiers .o dans le dossier build/
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Créer le répertoire build s'il n'existe pas
$(BUILDDIR):
	@echo "Creating build directory..."
	@mkdir $(BUILDDIR)

# Nettoyer les fichiers objets et l'exécutable
clean:
	@echo "Cleaning files..."
	del /F /Q $(BUILDDIR)\*.o
	del /F /Q $(TARGET)

# Recompiler tout
re: clean all
