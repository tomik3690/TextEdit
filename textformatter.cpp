#include "textformatter.h"
#include <QKeyEvent>

TextFormatter::TextFormatter()
{
    // Lista tagów HTML
    htmlTags << "a" << "abbr" << "address" << "div" << "section";
}

// Podświetlanie aktualnej linii
void TextFormatter::lineHighlighter(QTextEdit *textEdit)
{
    QTextEdit::ExtraSelection lineHighlight;
    lineHighlight.cursor = textEdit->textCursor();
    lineHighlight.format.setProperty(QTextFormat::FullWidthSelection, true);
    QColor color;
    color.setRgb(60, 60, 60);
    QBrush brush(color);
    lineHighlight.format.setBackground(brush);

    QList<QTextEdit::ExtraSelection> extras;
    extras << lineHighlight;
    textEdit->setExtraSelections( extras );
}

// Podświetlanie bloku
void TextFormatter::highlightBlock(QTextEdit *textEdit)
{/*
    int openings = 0, closings = 0;
    QTextBlock currentLine = textEdit->textCursor().block();
    for(int i = 0; i < htmlTags.length(); i++)
    {
        currentLine.text().append("test");
        //while(true)
        {
            QString openingRegExp = "<" + htmlTags.at(i) + ".*>";
            QRegExp openingExpression(openingRegExp);
            int openingIndex = currentLine.text().indexOf(openingExpression);

            if (openingIndex >= 0)
                openings++;

            QString closingRegExp = "</" + htmlTags.at(i) + ">";
            QRegExp closingExpression(closingRegExp);
            int closingIndex = currentLine.text().indexOf(closingExpression);

            if (closingIndex >= 0)
                closings++;

            currentLine.text().append("block");
            currentLine.next();

            if(openings == closings && openings != 0)
                break;
        }
    }*/
}

// Wcięcia wewnątrz elementów
void TextFormatter::tabsInsideElements(QTextEdit *textEdit)
{
    QTextBlock currentLine = textEdit->textCursor().block();
    if(currentLine.text().isEmpty() && !currentLine.text().contains("\t") && currentLine.userState() == -1)
    {
        QString tab = "\t";
        int tabsNumber = 0;
        int tabsCounter = currentLine.previous().text().indexOf(tab);

        while(tabsCounter >= 0)
        {
            tabsNumber++;
            tabsCounter = currentLine.previous().text().indexOf(tab, tabsCounter + tab.length());
        }

        QString tabs;
        int i = 0;
        while(i < tabsNumber)
        {
            tabs.append("\t");
            i++;
        }
        textEdit->textCursor().insertText(tabs);
        currentLine.setUserState(0);
    }
}

// Zamykanie elementów
void TextFormatter::elementsClosing(QTextEdit *textEdit)
{/*
    for(int i = 0; i < htmlTags.length(); i++)
    {
        QTextBlock currentLine = textEdit->textCursor().block();

        //currentLine.text();
        QString regExp = "<" + htmlTags.at(i) + ".*>";
        QString closing = "</" + htmlTags.at(i) + ">";
        QRegExp expression(regExp);
        int index = currentLine.text().indexOf(expression);

        if (index >= 0 && currentLine.userState() == -1)
        {
            currentLine.setUserState(0);
            currentLine.next().setUserState(0);

            QString tab = "\t";
            int tabsNumber = 0;
            int tabsCounter = currentLine.text().indexOf(tab);

            while(tabsCounter >= 0)
            {
                tabsNumber++;
                tabsCounter = currentLine.text().indexOf(tab, tabsCounter + tab.length());
            }

            QString tabs;
            int i = 0;
            while(i < tabsNumber)
            {
                tabs.append("\t");
                i++;
            }

            textEdit->textCursor().insertText("\n\n");
            textEdit->textCursor().insertText(tabs);
            textEdit->textCursor().insertText(closing);
            textEdit->moveCursor(QTextCursor::Up);
            textEdit->textCursor().insertText("\t");

            currentLine.setUserState(1);
        }
    }*/
}
