#ifndef WEIGHTED_COLUMN_H
#define WEIGHTED_COLUMN_H

class weightedColumn {
	private:
		int weight;
		int col;
	
	public:
		weightedColumn(int _weight = 0, int _col = -1);
		int getWeight();
		int getColumn();
        void changeWeight(int amount);
        weightedColumn operator+(weightedColumn other);
};

#endif