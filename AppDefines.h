#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QEventLoop>
#include <QTimer>


#define LOGD qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"

inline void delay(int ms){
    QEventLoop even;
    QTimer timer;
    timer.setInterval(ms);
    timer.setSingleShot(true);
    QObject::connect(&timer, SIGNAL(timeout()), &even, SLOT(quit()));
    timer.start();
    even.exec();
}

const QMap<QString, QString> LANG_MAP = {
    {"Unknown"          ,"Unknown"},
    {"English"          ,"English"},
    {"Tiếng Việt"       ,"Vietnamese"},
    {"Afrikaans"        ,"Afrikaans"},
    {"Azərbaycan dili"  ,"Azerbaijani"},
    {"Bahasa Indonesia" ,"Indonesian"},
    {"Bahasa Melayu"    ,"Malay"},
    {"Basa Jawa"        ,"Javanese"},
    {"Bisaya"           ,"Cebuano"},
    {"Čeština"          ,"Czech"},
    {"Dansk"            ,"Danish"},
    {"Deutsch"          ,"German"},
    {"Español"          ,"Spanish"},
    {"Filipino"         ,"Tagalog"},
    {"Français"         ,"French"},
    {"Guarani"          ,"Guarani"},
    {"Hausa"            ,"Hausa"},
    {"Hrvatski"         ,"Croatian"},
    {"Ikinyarwanda"     ,"Kinyarwanda"},
    {"Italiano"         ,"Italian"},
    {"Kiswahili"        ,"Swahili"},
    {"Magyar"           ,"Hungarian"},
    {"Malagasy"         ,"Malagasy"},
    {"Nederlands"       ,"Dutch"},
    {"Norsk (bokmål)"   ,"Norwegian"},
    {"Nederlands"       ,"Dutch"},
    {"Norsk (bokmål)"   ,"Norwegian"},
    {"Polski"           ,"Polish"},
    {"Português"        ,"Portuguese"},
    {"Română"           ,"Romanian"},
    {"Slovenčina"       ,"Slovak"},
    {"Slovenščina"      ,"Slovenian"},
    {"Suomi"            ,"Finnish"},
    {"Svenska"          ,"Swedish"},
    {"Türkçe"           ,"Turkish"},
    {"Ελληνικά"         ,"Greek"},
    {"български"        ,"Bulgarian"},
    {"Македонски"       ,"Macedonian"},
    {"Монгол"           ,"Mongolian"},
    {"Русский"          ,"Russian"},
    {"Српски"           ,"Serbian"},
    {"עברית"            ,"Hebrew"},
    {"اردو"             ,"Urdu"},
    {"العربية"          ,"Arabic"},
    {"فارسی"            ,"Persian"},
    {"አማርኛ"            ,"Amharic"},
    {"नेपाली"             ,"Nepali"},
    {"मराठी"            ,"Marathi"},
    {"हिन्दी"               ,"Hindi"},
    {"বাংলা"                ,"Bengali"},
    {"ਪੰਜਾਬੀ"               ,"Punjabi"},
    {"ગુજરાતી"              ,"Gujarati"},
    {"தமிழ்"            ,"Tamil"},
    {"తెలుగు"           ,"Telugu"},
    {"ಕನ್ನಡ"            ,"Kannada"},
    {"മലയാളം"           ,"Malayalam"},
    {"සිංහල"            ,"Sinhala"},
    {"ภาษาไทย"          ,"Thai"},
    {"မြန်မာဘာသာ"        ,"Burmese"},
    {"ភាសាខ្មែរ"        ,"Khmer"},
    {"한국어"              ,"Korean"},
    {"中文(台灣)"           ,"Taiwan"},
    {"中文(简体)"           ,"China"},
    {"中文(香港)"           ,"Hong Kong"},
    {"日本語"              ,"Japanese"}
};

#endif // APPDEFINES_H
