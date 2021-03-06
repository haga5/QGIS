/***************************************************************************
                              qgsfilterlineedit.h
                              ------------------------
  begin                : October 27, 2012
  copyright            : (C) 2012 by Alexander Bruy
  email                : alexander dot bruy at gmail dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSFILTERLINEEDIT_H
#define QGSFILTERLINEEDIT_H

#include <QLineEdit>
#include "qgis.h"
#include "qgis_gui.h"

class QToolButton;


/**
 * \class QgsFilterLineEdit
 * \ingroup gui
 * QLineEdit subclass with built in support for clearing the widget's value and
 * handling custom null value representations.
 *
 * When using QgsFilterLineEdit the value(), setValue() and clearValue() methods should be used
 * instead of QLineEdit's text(), setText() and clear() methods, and the valueChanged()
 * signal should be used instead of textChanged().
 **/
class GUI_EXPORT QgsFilterLineEdit : public QLineEdit
{

#ifdef SIP_RUN
    SIP_CONVERT_TO_SUBCLASS_CODE
    if ( qobject_cast<QgsFilterLineEdit *>( sipCpp ) )
      sipType = sipType_QgsFilterLineEdit;
    else
      sipType = NULL;
    SIP_END
#endif

    Q_OBJECT
    Q_PROPERTY( ClearMode clearMode READ clearMode WRITE setClearMode )
    Q_PROPERTY( QString nullValue READ nullValue WRITE setNullValue )
    Q_PROPERTY( QString defaultValue READ defaultValue WRITE setDefaultValue )
    Q_PROPERTY( QString value READ value WRITE setValue NOTIFY valueChanged )
    Q_PROPERTY( bool showClearButton READ showClearButton WRITE setShowClearButton )
    Q_PROPERTY( bool showSearchIcon READ showSearchIcon WRITE setShowSearchIcon )

  public:

    //! Behavior when clearing value of widget
    enum ClearMode
    {
      ClearToNull = 0, //!< Reset value to null
      ClearToDefault, //!< Reset value to default value (see defaultValue() )
    };
    Q_ENUM( ClearMode );

    /**
     * Constructor for QgsFilterLineEdit.
     * \param parent parent widget
     * \param nullValue string for representing null values
     */
    QgsFilterLineEdit( QWidget *parent SIP_TRANSFERTHIS = 0, const QString &nullValue = QString() );

    /**
     * Returns true if the widget's clear button is visible.
     * \see setShowClearButton()
     * \since QGIS 3.0
     */
    bool showClearButton() const { return mClearButtonVisible; }

    /**
     * Sets whether the widget's clear button is visible.
     * \param visible set to false to hide the clear button
     * \see showClearButton()
     * \since QGIS 3.0
     */
    void setShowClearButton( bool visible );

    /**
     * Returns the clear mode for the widget. The clear mode defines the behavior of the
     * widget when its value is cleared. This defaults to ClearToNull.
     * \see setClearMode()
     * \since QGIS 3.0
     */
    ClearMode clearMode() const { return mClearMode; }

    /**
     * Sets the clear mode for the widget. The clear mode defines the behavior of the
     * widget when its value is cleared. This defaults to ClearToNull.
     * \see clearMode()
     * \since QGIS 3.0
     */
    void setClearMode( ClearMode mode ) { mClearMode = mode; }

    /**
     * Sets the string representation for null values in the widget. This does not
     * affect the values returned for null values by value(), rather it only affects
     * the text that is shown to users when the widget's value is null.
     * \param nullValue string to show when widget's value is null
     * \see nullValue()
     */
    void setNullValue( const QString &nullValue ) { mNullValue = nullValue; }

    /**
     * Returns the string used for representating null values in the widget.
     * \see setNullValue()
     * \see isNull()
     */
    QString nullValue() const { return mNullValue; }

    /**
     * Define if a search icon shall be shown on the left of the image
     * when no text is entered
     * \param visible set to false to hide the search icon
     * \since QGIS 3.0
     */
    void setShowSearchIcon( bool visible );

    /**
     * Returns if a search icon shall be shown on the left of the image
     * when no text is entered
     * \since QGIS 3.0
     */
    bool showSearchIcon() const { return mSearchIconVisible; }

    /**
     * Sets the default value for the widget. The default value is a value
     * which the widget will be reset to if it is cleared and the clearMode()
     * is equal to ClearToDefault.
     * \param defaultValue default value
     * \see defaultValue()
     * \see clearMode()
     * \since QGIS 3.0
     */
    void setDefaultValue( const QString &defaultValue ) { mDefaultValue = defaultValue; }

    /**
     * Returns the default value for the widget. The default value is a value
     * which the widget will be reset to if it is cleared and the clearMode()
     * is equal to ClearToDefault.
     * \see setDefaultValue()
     * \see clearMode()
     * \since QGIS 3.0
     */
    QString defaultValue() const { return mDefaultValue; }

    /**
     * Sets the current text for the widget with support for handling null values.
     *
     * \param value The text to set. If a null string is provided, the text shown in the
     * widget will be set to the current nullValue().
     * \see value()
     */
    void setValue( const QString &value ) { setText( value.isNull() ? mNullValue : value ); }

    /**
     * Returns the text of this edit with support for handling null values. If the text
     * in the widget matches the current nullValue() then the returned value will be
     * a null string.
     *
     * \returns Current text (or null string if it matches the nullValue() property )
     * \see setValue()
     */
    QString value() const { return isNull() ? QString() : text(); }

    /**
     * Determine if the current text represents null.
     *
     * \returns True if the widget's value is null.
     * \see nullValue()
     */
    inline bool isNull() const { return text() == mNullValue; }

  public slots:

    /**
     * Clears the widget and resets it to the null value.
     * \see nullValue()
     * \since QGIS 3.0
     */
    virtual void clearValue();

  signals:

    /**
     * Emitted when the widget is cleared
     * \see clearValue()
     */
    void cleared();

    /**
     * Same as textChanged() but with support for null values.
     *
     * \param value The current text or null string if it matches the nullValue() property.
     */
    void valueChanged( const QString &value );

  protected:
    void mousePressEvent( QMouseEvent *e ) override;
    void mouseMoveEvent( QMouseEvent *e ) override;
    void focusInEvent( QFocusEvent *e ) override;
    void paintEvent( QPaintEvent *e ) override;
    void leaveEvent( QEvent *e ) override;

  private slots:
    void onTextChanged( const QString &text );

  private:

    bool mClearButtonVisible = true;
    bool mSearchIconVisible = false;

    ClearMode mClearMode = ClearToNull;

    QString mNullValue;
    QString mDefaultValue;
    QString mStyleSheet;
    bool mFocusInEvent = false;
    bool mClearHover = false;

    QSize mClearIconSize;
    QPixmap mClearIconPixmap;
    QPixmap mClearHoverPixmap;

    QSize mSearchIconSize;
    QPixmap mSearchIconPixmap;

    //! Returns true if clear button should be shown
    bool shouldShowClear() const;

    QRect clearRect() const;
    QRect searchRect() const;
};

/// @cond PRIVATE

/**
 * Private QgsFilterLineEdit subclass for use as a line edit in QgsSpinBox/QgsDoubleSpinBox
 * we let QgsFilterLineEdit handle display of the clear button and detection
 * of clicks, but override clearValue() and let Qgs(Double)SpinBox handle the clearing
 * themselves.
 */
class SIP_SKIP QgsSpinBoxLineEdit : public QgsFilterLineEdit
{
    Q_OBJECT

  public:

    QgsSpinBoxLineEdit( QWidget *parent = nullptr )
      : QgsFilterLineEdit( parent )
    {}

  public slots:

    virtual void clearValue() override
    {
      // don't change the value - let spin boxes handle that by detecting cleared() signal
      setCursor( Qt::IBeamCursor );
      setModified( true );
      emit cleared();
    }
};
/// @endcond

#endif // QGSFILTERLINEEDIT_H
