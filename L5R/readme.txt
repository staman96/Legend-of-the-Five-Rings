Εργασία Μαθήματος	Αντικειμενοστραφής Προγραμματισμός 2019/20

		Σκορδούλης Δημήτρης 1115201500145
		Μανωλάς Σταμάτιος 1115201400094

ΓΕΝΙΚΑ:

	Έχουμε ακολουθήσει τις οδηγίες της εκφώνησης και είδαμε και κάποιες διορθώσεις υπήρχαν στο φόρουμ. Το πρόγραμμα 
τρέχει με τη εντολή ./L5R . .Έχουμε προσπαθήσει να αποφύγουμε διπλότυπα δεδομένα όσον αφορά τις κάρτες. Το πρόγραμμα 
εχει γραφτεί σε C++. Το compilation γίνεται με την εντολή make, και η make clean σβήνει τα .ο αρχεία και τα 
εκτελέσιμα. Το πρόγραμμα αποδευσμεύει όλη τη μνήμη κανονικά, και το έχουμε τρέξει αρκετά με valgrind και δε βγάζει
κανένα πρόβλημα(0 ERRORS). Δοκιμάστηκε, επίσης, και στο linux09 της σχολής και έτρεχε χωρίς θέμα. Ενδεικτικά:
make clean && make && valgrind -v --leak-check=yes --show-leak-kinds=all --track-origins=yes ./L5R

ΠΑΡΑΤΗΡΗΣΕΙΣ, ΤΡΟΠΟΠΟΙΗΣΕΙΣ ΚΑΝΟΝΩΝ:

	Το παιχνίδι παίζεται με τουλάχιστον 2 παίχτες, και ακολουθούνται οι κανόνες που περιγράφονται στην εκφώνηση. Κάθε
παίχτης ξεκινάει το παιχνίδι με 4 κάρτες στο χέρι του και 4 Provices από Holdings, Personalities. Κάναμε αλλαγές 
στο δοσμένο κώδικα(DeckBuilder,Typeconverter). Υποθέσαμε ότι μία προσωπικότητα μπορεί να έχει μέχρι 10 πράσινες
κάρτες(follwers/items). Οι constructors των καρτών τύπου Item, Follower, Holding, Personality αρχικοποιούν τις τιμές
τους σύμφωνα με τα δοσμένα αρχεία txt. Στην αρχή κάθε γύρου, κάθε παίχτης κάνει harvest τα χρήματα που λαμβάνει από το
StrongHold και τα Holdings του. Μετά την πραγματοποίηση μιας αγοράς αυτά γίνοται tapped για να καλύψουν τη αξία της. 
Επίσης, σε κάθε γύρο στη Battle Phase κάθε παίχτης μπορεί να κάνει επίθεση μόνο μία φορά. Στη περίπτωση που η συνολική
επίθεση είναι ίση με τη συνολική άμυνα(μαζί κι αυτή του Provice x 2), ο επιτιθέμενος βγαίνει νικητής. Ακόμα, ο έλεγχος
για ανάγειξη νικητή γίνεται μετά από κάθε μάχη και όχι στο End Phase. Σε κάθε γύρο μετά την End Phase υπάρχει η δυνατότητα
τερματισμού του παιχνιδιού από το χρήστη ούτως ώστε σε περίπτωση ισοπαλίας, είτε αδυναμίας ανάδειξης νικητή, το παιχνίδι 
μπορεί να διακοπεί. Επιπρόσθετα, όταν το Fate Deck ξεμείνει από κάρτες, τότε ο παίχτης δε μπορεί να τραβήξει άλλες κάρτες
στο χέρι του και ενημερώνεται με σχετικό μύνημα. Όμως, όταν το Dynasty Deck αδειάσει, τότε, όποτε ο παίχτης χάνει το
Provice από το οποίο αγοράζει τη κάρτα. Όταν, μείνει με ένα Provice, τότε δε μπορεί να αγοράσει τη τελευταία κάρτα διότι
τότε θα έχανε.

ΕΠΕΞΗΓΗΣΗ ΚΩΔΙΚΑ:
	
main.cpp:
	Στην main επιλέγεται ο αριθμός των παιχτών, δημιουργείται το GameBoard και ξεκινάει το GamePlay.

GameBoard.cpp/.h:
	Εδώ καλούνται οι 5 φάσεις, γίνεται η επίλυση των μαχών και ο έλεγχος για ανάδειξη νικητή. Επίσης, υπολοποιείται η
εκτύπωση της αρένας και των στατιστικών του παιχνιδιού.

Player.cpp/.h:
	Το μεγαλύτερο μέρος του παιχνιδιού υλοποιείται στο Player, που περιλαμβάνει τη δημιουργία των Decks, τις δυνατότητες
κάθε παίχτη σε όλες τις φάσεις.

GreenCards.cpp/.h, BlackCards.cpp/.h:
	Πρόκειται για υποκλάσεις των Item, Follower, Holding, Personality τύπων καρτών που περιέχουν τους constructors για
την δημιουργία όλων των καρτών.

Περισσότερες λεπτομέρειες περιέχονται στα σχόλια του κώδικα.