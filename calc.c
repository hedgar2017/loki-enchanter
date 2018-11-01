#include <stdio.h>
#include <stdlib.h>

static double weaponChances[19] = {0.00,
	1.00, // +1
	1.00, // +2
	1.00, // +3
	1.00, // +4
	0.90, // +5
	0.80, // +6
	0.72, // +7
	0.72, // +8
	0.70, // +9
	0.68, // +10
	0.60, // +11
	0.60, // +12
	0.60, // +13
	0.50, // +14
	0.40, // +15
	0.30, // +16
	0.25, // +17
	0.20, // +18
};

static double armorChances[15] = {0.00,
	1.00, // +1
	1.00, // +2
	1.00, // +3
	0.60, // +4
	0.60, // +5
	0.60, // +6
	0.60, // +7
	0.60, // +8
	0.50, // +9
	0.50, // +10
	0.50, // +11
	0.50, // +12
	0.40, // +13
	0.30, // +14
};

typedef enum {
	TYPE_WEAPON = 0,
	TYPE_ARMOR = 1
} Type;

int main(int argc, char **argv) {	
	int safe = 3;
	
	for (int t = 0; t <= 1; ++t) {
		double *chances = NULL;
		int limit = 0;
		
		switch ((Type) t) {
		case TYPE_WEAPON:
			chances = weaponChances;
			limit = 18;
			break;
		case TYPE_ARMOR:
			chances = armorChances;
			limit = 14;
			break;
		}
	
		for (int l = safe + 1; l <= limit; ++l) {
			double levelProbability = 1.0;
			for (int i = safe + 1; i <= l; ++i) {
				levelProbability *= chances[i];
			}
			
			double scrollAmountPerTry = 0.0;
			for (int i = safe + 1; i <= l; ++i) {
				double probability = 1.0;
				for (int j = safe + 1; j <= i; ++j) {
					probability *= chances[j-1];
				}
				scrollAmountPerTry += probability;
			}
			
			double scrollAmount = scrollAmountPerTry / levelProbability + safe;
			double costGradeWeaponS = scrollAmount / 175.0;
			double costGradeArmorA = scrollAmount / 250.0;
			double costGradeArmorS = scrollAmount / 200.0;
			
			switch ((Type) t) {
			case TYPE_WEAPON:
				printf("+%2d %8.6lf %5.3lf %9.3lf %7.3lf\n",
					l,
					levelProbability,
					scrollAmountPerTry,
					scrollAmount,
					costGradeWeaponS
				);
				break;
			case TYPE_ARMOR:
				printf("+%2d %8.6lf %5.3lf %9.3lf %7.3lf %7.3lf\n",
					l,
					levelProbability,
					scrollAmountPerTry,
					scrollAmount,
					costGradeArmorA,
					costGradeArmorS
				);
				break;
			}
			
		}
		if (t < 1) printf("%s", "\n");
	}
	
	return EXIT_SUCCESS;
}