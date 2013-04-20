#include "character.h"

Character::Character() {
	setName("??????");

	std::string textureNames[] = {"img/warrior_menu.tga", "img/thief_menu.tga", "img/white_menu.tga", "img/black_menu.tga", "img/monk_menu.tga", "img/red_menu.tga"};
	textures.createTextures(JOBSCOUNT, textureNames);


	// initialize the possible random names
	std::string names[JOBSCOUNT][10] = {
		// warrior names
		{"Argus", "Arus", "Banon", "Baron", "Desh",
		"Doma", "Giott", "Leo", "Sasuun", "Zeza"},

		// thief names
		{"Baku", "Biggs", "Blank", "Daryl", "Gerad",
		"Kelga", "Puck", "Sarisa", "Tuss", "Wedge"},

		// white mage names
		{"Elia", "Kuku", "Jenica", "Luca", "Mikoto", 
		"Noah", "Ruby", "Sara", "Sarina", "Sherko"},

		// black mage names
		{"Delila", "Gilles", "Gungho", "Homac", "Kokkol",
		"Koko", "Nina", "Stella", "Topapa", "Zok"},
		
		// monk names
		{"Arvis", "Cinna", "Drogan", "Duncan", "Gorn",
		"Maduin", "Marcus", "Owain", "Owzer", "Walz"},

		// red mage names
		{"Duane", "Elayne", "Gill", "KluYa", "Kory",
		"Lalibo", "Lola", "Mid", "Tot", "Yura"}};
	for (int i = 0; i < JOBSCOUNT; i++) {
		for (int j = 0; j < 10; j++) {
			randomNames[i][j] = names[i][j];
		}
	}

	// initialize character to not have any spells
	for (int lvl = 0; lvl < 8; lvl++) {
		for (int slot = 0; slot < 3; slot++) {
			spells[lvl][slot] = -1;
		}
	}

	// no status effects
	statusBits = 0;
}

Character::~Character() {
}

Character::Character(const Character &cSource) {
	makeCopy(cSource);
}

Character &Character::operator=(const Character &rhs) {
	// check for self-assignemnt
	if (this == &rhs) {
		return *this;
	}

	// perform assignment operation
	makeCopy(rhs);

	// return the existing object
	return *this;
}

void Character::makeCopy(const Character &source) {
	name = source.name;
	job = source.job;

	for (int i = 0; i < STATSCOUNT; i++) {
		attributes[i] = source.attributes[i];
	}

	// no need to copy textures yet, 
	// for now every character uses same textures
	// textures = source.textures;
}

void Character::initStats() {
	attributes[LEVEL] = 1;
	attributes[EXP] = 0;
	switch (job) {
		case WARRIOR: {
			attributes[MAGLEVEL] = 0;

			// initial warrior stats (hpmax, mpmax, str, agl, ..., def, eva)
			int attrValues[] = {35, 0, 10, 8, 1, 15, 8, 5, 18, 0, 61};

			// initial warrior equip (knife and clothes)
			int equipValues[5][5] = {{10, 5, 10, 0, 0}, {-1, 0, 0, 0, 0}, 
				{-1, 0, 0, 0, 0}, {15, 0, 0, 1, -2}, {-1, 0, 0, 0, 0}};

			// initialize character stats and equipment
			fillValues(attrValues, equipValues);
			break;
		} case THIEF: {
			attributes[MAGLEVEL] = 0;

			// initial thief stats (hpmax, mpmax, str, agl, ..., def, eva)
			int attrValues[] = {30, 0, 5, 15, 1, 5, 15, 2, 30, 0, 73};

			// initial thief equip (knife and clothes)
			int equipValues[5][5] = {{10, 5, 10, 0, 0}, {-1, 0, 0, 0, 0}, 
				{-1, 0, 0, 0, 0}, {15, 0, 0, 1, -2}, {-1, 0, 0, 0, 0}};

			// initialize character stats and equipment
			fillValues(attrValues, equipValues);
			break;
		} case WHITE: {
			attributes[MAGLEVEL] = 1;

			// initial white mage stats (hpmax, mpmax, str, agl, ..., def, eva)
			int attrValues[] = {33, 10, 5, 5, 15, 8, 5, 2, 10, 0, 58};

			// initial white mage equip (staff and clothes)
			int equipValues[5][5] = {{14, 6, 0, 0, 0}, {-1, 0, 0, 0, 0}, 
				{-1, 0, 0, 0, 0}, {15, 0, 0, 1, -2}, {-1, 0, 0, 0, 0}};

			// initialize character stats and equipment
			fillValues(attrValues, equipValues);
			break;
		} case BLACK: {
			attributes[MAGLEVEL] = 1;

			// initial black mage stats (hpmax, mpmax, str, agl, ..., def, eva)
			int attrValues[] = {25, 10, 3, 5, 20, 2, 10, 1, 13, 0, 58};

			// initial black mage equip (knife and clothes)
			int equipValues[5][5] = {{10, 5, 10, 0, 0}, {-1, 0, 0, 0, 0}, 
				{-1, 0, 0, 0, 0}, {15, 0, 0, 1, -2}, {-1, 0, 0, 0, 0}};

			// initialize character stats and equipment
			fillValues(attrValues, equipValues);
			break;
		} case MONK: {
			attributes[MAGLEVEL] = 0;

			// initial monk stats (hpmax, mpmax, str, agl, ..., def, eva)
			int attrValues[] = {33, 0, 12, 5, 1, 10, 5, 14, 13, 5, 55};

			// initial monk equip (staff and clothes)
			int equipValues[5][5] = {{14, 6, 0, 0, 0}, {-1, 0, 0, 0, 0}, 
				{-1, 0, 0, 0, 0}, {15, 0, 0, 1, -2}, {-1, 0, 0, 0, 0}};

			// initialize character stats and equipment
			fillValues(attrValues, equipValues);
			break;
		} case RED: {
			attributes[MAGLEVEL] = 1;

			// initial red mage stats (hpmax, mpmax, str, agl, ..., def, eva)
			int attrValues[] = {30, 10, 5, 10, 10, 5, 5, 2, 22, 0, 63};

			// initial red mage equip (knife and clothes)
			int equipValues[5][5] = {{10, 5, 10, 0, 0}, {-1, 0, 0, 0, 0}, 
				{-1, 0, 0, 0, 0}, {15, 0, 0, 1, -2}, {-1, 0, 0, 0, 0}};

			// initialize character stats and equipment
			fillValues(attrValues, equipValues);
			break;
		} default:
			break;
	}
	attributes[HP] = attributes[HPMAX];
	attributes[MP] = attributes[MPMAX];
}

void Character::fillValues(int initAttrs[STATSCOUNT], int initEquip[5][5]) {
	for (int i = HPMAX; i < STATSCOUNT; i++) {
		attributes[i] = initAttrs[i - HPMAX];
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			equipment[i][j] = initEquip[i][j];
		}
	}
}

void Character::render(int x, int y) {
	render(job, x, y);
}

void Character::render(Jobs job, int x, int y) {
	glBindTexture(GL_TEXTURE_2D, textures.getTexture(job));
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(x, y, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(x, y - 148, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(x + 120, y - 148, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(x + 120, y, 0.0f);
	glEnd();
}

void Character::setName(std::string newName) {
	name = newName;
}

std::string Character::getName() {
	return name;
}

void Character::setRandomName() {
	name = randomNames[job][rand() % 10];
}

void Character::setJob(Jobs newJob) {
	if (newJob >= WARRIOR && newJob < JOBSCOUNT) {
		job = newJob;
	}
}

Character::Jobs Character::getJob() {
	return job;
}

std::string Character::getJobName() {
	return getJobName(job);
}

std::string Character::getJobName(Jobs job) {
	switch (job) {
		case WARRIOR:
			return "Warrior";
		case THIEF:
			return "Thief";
		case WHITE:
			return "White Mage";
		case BLACK:
			return "Black Mage";
		case MONK:
			return "Monk";
		case RED:
			return "Red Mage";
		default:
			return "";
	}
}

int Character::getAttribute(Stats s) {
	if (s < ATK) {
		// attribute unmodified by equipment
		return attributes[s];
	}

	// return value modified by current equipment
	// TODO: Some of these formulas are outdated and
	//       from the original FF1, (specifically monk)
	if (s == ATK) {
		if (job == MONK && equipment[0][0] == -1) {
			// monk not wearing weapon
			return attributes[LEVEL] * 2;
		} else if (job == MONK || job == BLACK) {
			// monk or blm with weapon: weaonatk + str/2 + 1
			return equipment[0][1] + attributes[STR] / 2 + 1;
		}
		// weaponatk + str/2
		return equipment[0][1] + attributes[STR] / 2;
	} else if (s == ACC) {
		// weaponacc + characteracc
		return equipment[0][2] + attributes[ACC];
	} else if (s == DEF) {
		if (job == MONK) {
			// monk defense = level
			return attributes[LEVEL];
		}

		// total defense of equipment
		int totalEquippedDef = 0;
		for (int i = 0; i < 4; i++) {
			totalEquippedDef += equipment[i][3];
		}
		return totalEquippedDef + attributes[DEF];
	} else if (s == EVA) {
		// 48 + agl - armor weight
		// armor weights are represented with negative eva
		int totalWeight = 0;
		for (int i = 0; i < 4; i++) {
			totalWeight += equipment[i][4];
		}
		return attributes[EVA] + totalWeight;
	}
	return 0;
}

std::string Character::getHPFraction() {
	return getFraction(HP, HPMAX);
}

std::string Character::getMPFraction() {
	return getFraction(MP, MPMAX);
}

std::string Character::getFraction(Stats num, Stats denom) {
	std::string cur = std::to_string(attributes[num]);
	std::string max = std::to_string(attributes[denom]);

	// add whitespace
	const int DIGITS = 4;	// max digits
	int spacesNeeded = DIGITS - cur.length();
	cur.insert(0, spacesNeeded, ' ');

	spacesNeeded = DIGITS - max.length();
	max.insert(0, spacesNeeded, ' ');

	// return fraction format
	return (cur + '/' + max);
}

int Character::addHP(int amount) {
	int excess = 0;
	attributes[HP] += amount;
	if (attributes[HP] > attributes[HPMAX]) {
		// hp exceeds maxhp
		excess = attributes[HP] - attributes[HPMAX];
		attributes[HP] = attributes[HPMAX];
	} else if (attributes[HP] < 0) {
		// hp fell below 0
		excess = attributes[HP];
		attributes[HP] = 0;
	}

	// calculate how much hp was added
	return (amount - excess);
}

bool Character::setStatus(unsigned int status) {
	if (statusBits & (1 << status)) {
		return 0;	// character already has status
	}

	// set status bit
	statusBits |= 1 << status;
	return 1;	// status successfully set
}

bool Character::removeStatus(unsigned int status) {
	if (statusBits & (1 << status)) {
		// clear status bit
		statusBits &= ~(1 << status);
		return 1;	// 	status successfully removed
	}
	return 0;	// character does not have status
}

int Character::expToNext() {
	// experience needed for first 20 levels
	int expNeeded[] = {0, 14, 42, 98, 196, 350, 574, 882, 1288, 1806, 2450, 3234, 4172, 5278, 6566, 8050, 9744, 11662, 13818, 16226};

	if (attributes[LEVEL] >= 20) {
		return 0;	// only supporting first 20 levels for now
	}

	return (expNeeded[attributes[LEVEL]] - attributes[EXP]);
}

int Character::getSpell(int level, int slot) {
	level--;	// convert to 0-based index
	if (level < 0 || level > 7 || slot < 0 || slot > 2) {
		return 0; // out of bounds
	}
	return spells[level][slot];
}

int Character::getEquip(int slot) {
	if (slot < 0 || slot > 4) {
		return 0; // out of bounds
	}
	return equipment[slot][0];
}

bool Character::canEquip(int type) {
	if (type == -1) {
		return 0;
	}
	return 1;
}

void Character::setEquip(int slot, int id, int values[4]) {
	if (slot < 0 || slot > 4) {
		return; // out of bounds
	}
	equipment[slot][0] = id;
	for (int i = 0; i < 4; i++) {
		equipment[slot][i + 1] = values[i];
	}
}

void Character::removeEquip(int slot) {
	int values[4] = {0, 0, 0, 0};
	setEquip(slot, -1, values);
}
