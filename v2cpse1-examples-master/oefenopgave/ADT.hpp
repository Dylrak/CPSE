#ifndef ADT_HPP
#define ADT_HPP

template< typename T, int N >
class set
{
private:
T a[N];
int used;
public:
	set(): used ( 0 );

	bool contains( T item ) {
		for (int i = 0; i < N; i++) {
			if (a[i] == item) {
				return true;
			}
		}
		return false;
	}
	void add ( T item ) {
		if (!contains ( item ) && used < N) {
			a[used++] = item;
		}
	}
	void remove ( T item ) {
		int position;
		bool exists = false;
		for (int i = 0; i <= used; i++) {
			if ( a[i] == item) {
				position = i;
				exists = true;
				break;
			}
		}
		if (exists) {
			for (int i = position; i < used - 1; i++) {
				a[i] = a[i + 1];
			}
			
		}
	}
};

#endif // ADT_HPP
