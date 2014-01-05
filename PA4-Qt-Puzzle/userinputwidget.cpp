/*
 * Brandon Barber
 * bsbarber@usc.edu
 */
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <string>
#include "userinputwidget.h"

/**
 * Constructs a UserInputWidget
 */
UserInputWidget::UserInputWidget()
{
	text1 = new QLineEdit();
	text2 = new QLineEdit();
	text3 = new QLineEdit();
	
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(new QLabel("Dimension:"));
	layout->addWidget(text1);
	layout->addWidget(new QLabel("Num Moves:"));
	layout->addWidget(text2);
	layout->addWidget(new QLabel("Seed:"));
	layout->addWidget(text3);
}

/**
 * Returns the string of text in the first box
 * @return string of first box
 */
std::string UserInputWidget::getBoardSize()
{
	return text1->text().toUtf8().constData();
}

/**
 * Returns the string of text in the second box
 * @return string of second box
 */
std::string UserInputWidget::getNumMoves()
{
	return text2->text().toUtf8().constData();
}

/**
 * Returns the string of text in the second box
 * @return string of second box
 */
std::string UserInputWidget::getSeed()
{
	return text3->text().toUtf8().constData();
}

/**
 * Destroys the UserInputWidget
 */
UserInputWidget::~UserInputWidget()
{
	
}
