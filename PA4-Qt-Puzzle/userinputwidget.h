/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#ifndef USERINPUTWIDGET_H
#define USERINPUTWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <string>

class UserInputWidget : public QWidget
{
	Q_OBJECT
	public:
		UserInputWidget();
		~UserInputWidget();
		std::string getBoardSize();
		std::string getNumMoves();
		std::string getSeed();
	private:
		QLineEdit* text1,* text2,* text3;
		
};
#endif
