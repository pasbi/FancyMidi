#ifndef MIDICOMMANDSELECTSETTING_H
#define MIDICOMMANDSELECTSETTING_H

#include <QStringList>
#include "Settings/setting.h"
#include "Domain/domain.h"
#include <QDebug>
#include "nordstage2.h"
#include <QDataStream>

class MidiCommandSelectSetting : public Setting
{
    Q_OBJECT
public:
    MidiCommandSelectSetting(Node *parent, QString name, QString tooltip);
    MidiCommandSelectSetting(QDataStream& stream);
    void writeToStream(QDataStream &stream) const;
    ~MidiCommandSelectSetting();


    double min() const;
    double max() const;
    double value() const;
    int index() const;
    QStringList items() const;

    Domain::Type domainType() const;
    Domain* domain() const { return _domain; }


    int currentCategory() const { return _currentCategory; }
    int currentProperty() const { return _currentProperty; }
    int channel() const { return _currentChannel; }


public slots:
    void setDouble(double d);
    void setInt(int i);
    void setIndex(int i);
    void setCategoryIndex(int i);
    void setPropertyIndex(int i);
    void setChannel(int i);

private:
    int _currentCategory = 0;
    int _currentProperty = 0;
    int _currentChannel = 0;
    QString key() const {
        return QString("%1.%2")
                .arg(NordStage2::categories()[_currentCategory])
                .arg(NordStage2::properties(_currentCategory)[_currentProperty]); }
    MidiKey midiKey() const;
    Domain* _domain = 0;
    void updateDomain();


signals:
    void sendMidi();

    REGISTER_DECL_SETTINGTYPE(MidiCommandSelectSetting);
};

#endif // MIDICOMMANDSELECTSETTING_H