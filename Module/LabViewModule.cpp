#include "LabViewModule.h"

LabViewModule::LabViewModule(PolyboxModule *polybox, QObject *parent) :
    QObject(parent), AbstractModule(polybox)
{
    initAll();
}


void LabViewModule::initAll()
{
    _mediaPlayer = NULL;
    setGlobalColor( QColor( 0, 0, 0 ) );
    initFaceClass();
}

void LabViewModule::setGlobalColor(QColor c)
{
    setAllFacesColor(c);
}

void LabViewModule::sendGlobalColor()
{
    /*QString param(QString::number(MCODE_LABVIEW_SET_GLOBAL_RGB)+" R");
    param+=QString::number(_currentColor.red());
    param+=" E";
    param+= QString::number(_currentColor.green());
    param+=" P";
    param+=QString::number(_currentColor.blue());
    param+=" I";
    param+=QString::number(_currentColor.alpha());
    SerialPort::getSerial()->sendMCode( param );
    */
}

void LabViewModule::sendController(LabViewController c)
{
    int mcode = MCODE_LABVIEW_SET_CONTROLLER;
    if ( c == Software )
    {
        PolyboxModule::getInstance()->connector()->sendMCode( QString::number(mcode) + " S1" );
    }
    else if ( c == Manual)
    {
        PolyboxModule::getInstance()->connector()->sendMCode( QString::number(mcode) + " H1" );
    }
    else
    {
        PolyboxModule::getInstance()->connector()->sendMCode( QString::number(mcode) + " H1" );
    }
}

QStringList LabViewModule::getAllCamera(QString path_directory)
{
    /*
    QList<QByteArray> cameras = QCamera::availableDevices();
    QStringList list_cameras;
    foreach(const QByteArray &deviceName, cameras )
    {
        list_cameras.append( QCamera::deviceDescription(deviceName) );
    }
    return list_cameras;*/
    QDir cameras_dir(path_directory);
    return cameras_dir.entryList(QStringList("video*"),QDir::System, QDir::Name) ;
}

void LabViewModule::toggleInter()
{
    _isOn = !_isOn;
    _polybox->connector()->sendMCode( QString::number(MCODE_LABVIEW_SET_STATUS)+" S"+QString::number(_isOn) );
}

void LabViewModule::setConnectedColor()
{
    PolyboxModule::getInstance()->connector()->sendMCode( MCODE_START_CONNECTION );
    //setAllFacesColor( QColor(0,150,120,255) );
    //setAllFacesLight( 120, true, true );
}

void LabViewModule::initFaceClass()
{
    _top.name="top";
    _top.id = FACE_TOP_ID;

    _bot.name="bot";
    _bot.id = FACE_BOT_ID;

    _left.name="left";
    _left.id = FACE_LEFT_ID;

    _right.name="right";
    _right.id = FACE_RIGHT_ID;

    _back.name="back";
    _back.id = FACE_BACK_ID;

    _front.name="front";
    _front.id = FACE_FRONT_ID;
}

bool LabViewModule::isReady() const
{
    return true;
}

void LabViewModule::setCamera(QString cam)
{
    _selectedCamera = cam;
}

QProcess* LabViewModule::startCamera(QProcess* process, QString camera)
{
    if ( process != NULL )
    {
        process->kill();
    }

    QString command = "vlc";
    QStringList parameters;
    parameters << "v4l2:///dev/"+camera<<"--video-filter"<<"rotate{angle="+QString::number(Config::webCamRotation())+"}" ;
    process = new QProcess( );
    process->start( command, parameters );
    return process;
}

void LabViewModule::startCamera()
{
    _mediaPlayer = startCamera( _mediaPlayer, _selectedCamera );
}
void LabViewModule::startBoardcast()
{
    if ( _mediaPlayer != NULL )
    {
        _mediaPlayer->kill();
    }

    QString command = "vlc";
    QStringList parameters;
    parameters << "v4l2:///dev/"+_selectedCamera<<"--video-filter"<<"rotate{angle="+QString::number(Config::webCamRotation())+"}"<<"--file-logging"<<"--logfile=vlc-log.txt"
               <<"--sout=#duplicate{dst=display,dst=\"transcode{vcodec=WMV2,vb=800,scale=1,acodec=wma2,ab=128,channels=2,samplerate=44100}:http{mux=asf,dst="+Config::broadcastIP()+":"+QString::number(Config::broadcastPort())+"/,name=\"PolyBox3D LiveStream\"}\"";
    _mediaPlayer = new QProcess( this );
    _mediaPlayer->start( command, parameters );

}

void LabViewModule::startRecording()
{
    // is an already starting mediaplayer process ? If yes, we kill him
    //It's better, especially since the user can kill the process without Qt App
    if ( _mediaPlayer != NULL )
    {
        _mediaPlayer->kill();
    }

    //  Get output filename
    QString fileName = QFileDialog::getSaveFileName(NULL,
                                                    tr("Vidéo de sortie"),
                                                    "./output_video.ps");
    //start Recording

    QString command = "vlc";
    QStringList parameters;
    parameters << "v4l2:///dev/"+_selectedCamera<<"--video-filter"<<"rotate{angle="+QString::number(Config::webCamRotation())+"}"<<"--file-logging"<<"--logfile=vlc-log.txt"
               <<"--sout=#duplicate{dst=display,dst=\"transcode{vcodec=h264,vb=0,scale=0,acodec=mpga,ab=128,channels=2,samplerate=44100}:std{access=file,mux=mp4,dst='"+fileName+"'}\"";
    _mediaPlayer = new QProcess( this );
    _mediaPlayer->start( command, parameters );
}
void LabViewModule::setAllFacesColor(QColor c)
{
    _left.setColor( c );
    _right.setColor( c );
    _top.setColor( c );
    _bot.setColor( c );
    _back.setColor( c );
    _front.setColor( c );
}

void LabViewModule::setAllFacesLight(int light, bool horizontale, bool verticale)
{
    if ( horizontale )
    {
        _left.setHIntensity( light);
        _right.setHIntensity( light);
        _top.setHIntensity( light);
        _bot.setHIntensity( light);
        _back.setHIntensity( light);
        _front.setHIntensity( light);
    }
    if ( verticale)
    {
        _left.setVIntensity( light);
        _right.setVIntensity( light);
        _top.setVIntensity( light);
        _bot.setVIntensity( light);
        _back.setVIntensity( light);
        _front.setVIntensity( light);
    }
}

void LabViewModule::exportXmlAllFaces(QXmlStreamWriter *xml)
{
    _top.toXml( xml );
    _bot.toXml( xml );
    _left.toXml( xml );
    _right.toXml( xml );
    _back.toXml( xml );
    _front.toXml( xml );
}

void LabViewModule::parseMCode(QByteArray stream)
{
    QString str(stream);
    long value = SerialPort::embeddedstr2l( str, 0 );
    int idx = 0;
    int size = str.size();
    switch ( value )
    {
    case MCODE_LABVIEW_GET_GLOBAL_RGB:
    {
        SerialPort::nextField( str, idx);
        while ( idx < size )
        {
            if ( str[idx] == 'R' )
            {
                SerialPort::nextValue( str, idx);
                currentColor()->setRed( SerialPort::embeddedstr2l( str, idx ));
                setAllFacesColor( *currentColor() );
            }
            if ( str[idx] == 'E' )
            {
                SerialPort::nextValue( str, idx);
                currentColor()->setGreen( SerialPort::embeddedstr2l( str, idx ) );
                setAllFacesColor( *currentColor() );
            }
            if ( str[idx] == 'P' )
            {
                SerialPort::nextValue( str, idx);
                currentColor()->setBlue( SerialPort::embeddedstr2l( str, idx ) );
                setAllFacesColor( *currentColor() );
            }
            if ( str[idx] == 'I' )
            {
                SerialPort::nextValue( str, idx);
                currentColor()->setAlpha( SerialPort::embeddedstr2l( str, idx ) );
                setAllFacesColor( *currentColor() );
            }
            SerialPort::nextField( str, idx);
        }
    }
        break;
    case MCODE_LABVIEW_GET_FACE_RGB:
    {
  /*      SerialPort::nextField( str, idx);
        Face* face = &_top;
        while ( idx < size )
        {
            if ( str[idx] == 'S' )
            {
                SerialPort::nextValue( str, idx);
                face
            }
            if ( str[idx] == 'R' )
            {
                SerialPort::nextValue( str, idx);
                _currentColor.setRed( SerialPort::embeddedstr2l( str, idx ) );
            }
            if ( str[idx] == 'E' )
            {
                SerialPort::nextValue( str, idx);
                _currentColor.setGreen( SerialPort::embeddedstr2l( str, idx ) );
            }
            if ( str[idx] == 'P' )
            {
                SerialPort::nextValue( str, idx);
                _currentColor.setBlue( SerialPort::embeddedstr2l( str, idx ) );
            }
            if ( str[idx] == 'I' )
            {
                SerialPort::nextValue( str, idx);
                _currentColor.setAlpha( SerialPort::embeddedstr2l( str, idx ) );
            }
            SerialPort::nextField( str, idx);
        }*/
    }
        break;
    case MCODE_LABVIEW_GET_GLOBAL_I:
    {
        SerialPort::nextField( str, idx);
        while ( idx < size )
        {
            if ( str[idx] == 'X' )
            {
                SerialPort::nextValue( str, idx);

                setAllFacesLight( SerialPort::embeddedstr2l( str, idx ), true, false );

            }
            if ( str[idx] == 'Y' )
            {
                SerialPort::nextValue( str, idx);
                setAllFacesLight( SerialPort::embeddedstr2l( str, idx ), false, true );
            }
            SerialPort::nextField( str, idx);
        }
        /*SerialPort::nextField( str, idx);
        SerialPort::parseTrueFalse( &_, str[idx] );*/
    }
        break;
    case MCODE_LABVIEW_GET_FACE_I:
    {
        SerialPort::nextField( str, idx);
        int x, y, id ;
        x=y=id=0;
        while ( idx < size )
        {
            if ( str[idx] == 'P' )
            {
                SerialPort::nextValue( str, idx);
                id = SerialPort::embeddedstr2l( str, idx );
            }
            if ( str[idx] == 'X' )
            {
                SerialPort::nextValue( str, idx);
                x = SerialPort::embeddedstr2l( str, idx );
                setFaceLight( SerialPort::embeddedstr2l( str, idx ), false, true );
            }
            if ( str[idx] == 'Y' )
            {
                SerialPort::nextValue( str, idx);
                y = SerialPort::embeddedstr2l( str, idx );
                setFaceLight( SerialPort::embeddedstr2l( str, idx ), false, true );
            }
            SerialPort::nextField( str, idx);
        }
        setFaceLight( id, x, y );
    }
        break;
    default:
        break;
    }
   emit updateUI();
}

void LabViewModule::forceSendUpdate()
{
    _top.sendValues();
    _bot.sendValues();
    _right.sendValues();
    _left.sendValues();
    _front.sendValues();
    _back.sendValues();
}

void LabViewModule::saveToXmlFile(QString filename)
{
    QFile* file = new QFile(filename);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(NULL,
                              tr("Save to XML file"),
                              tr("Couldn't write to ")+filename,
                              QMessageBox::Ok);
        return;
    }
    QXmlStreamWriter xml(file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    xml.writeStartElement("profile");
    xml.writeTextElement("name", filename.split("/").last().split(".").first());
    //COLOR
    xml.writeStartElement("globalcolor");
    xml.writeTextElement("red", QString::number( getGlobalColor()->red()));
    xml.writeTextElement("green", QString::number( getGlobalColor()->green()) );
    xml.writeTextElement("blu", QString::number( getGlobalColor()->blue()) );
    xml.writeTextElement("intensity", QString::number( getGlobalColor()->alpha()) );
    xml.writeEndElement();//color

    exportXmlAllFaces( &xml );

    xml.writeEndElement();//profile
    xml.writeEndDocument();
    file->close();
}

void LabViewModule::parseGlobalcolor(QXmlStreamReader *xml)
{
    while(!(xml->tokenType() == QXmlStreamReader::EndElement && xml->name() == "globalcolor"))
    {
        if(xml->tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml->name() == "red")
            {
                xml->readNext();
                currentColor()->setRed( xml->text().toString().toInt() );
            }
            if(xml->name() == "green")
            {
                xml->readNext();
                currentColor()->setGreen( xml->text().toString().toInt() );
            }
            if(xml->name() == "blu")
            {
                xml->readNext();
                currentColor()->setBlue( xml->text().toString().toInt() );
            }
            if(xml->name() == "intensity")
            {
                xml->readNext();
                currentColor()->setAlpha( xml->text().toString().toInt() );
            }
        }
        xml->readNext();
    }
    setGlobalColor(*currentColor());
    //sendGlobalColor(); // we update firmware data
}
void LabViewModule::setFaceLight(int face_id, int horizontale, int verticale)
{
    if ( face_id == FACE_TOP_ID )
        setFaceLight( "top", horizontale, verticale );
    if ( face_id == FACE_BOT_ID )
        setFaceLight( "bot", horizontale, verticale );
    if ( face_id == FACE_LEFT_ID )
        setFaceLight( "left", horizontale, verticale );
    if ( face_id == FACE_RIGHT_ID )
        setFaceLight( "right", horizontale, verticale );
    if ( face_id == FACE_BACK_ID )
        setFaceLight( "back", horizontale, verticale );
    if ( face_id == FACE_FRONT_ID )
        setFaceLight( "front", horizontale, verticale );
}

void LabViewModule::setFaceLight(QString face_name, int horizontale, int verticale)
{
    Face* cface = NULL;
    if ( face_name == "top" )
    {
        cface = &_top;
    }
    if ( face_name == "bot" )
    {
        cface = &_bot;
    }
    if ( face_name == "left" )
    {
         cface = &_left;
    }
    if ( face_name == "right" )
    {
        cface = &_right;
    }
    if ( face_name == "back" )
    {
        cface = &_back;
    }
    if ( face_name == "front" )
    {
        cface = &_front;
    }
    if ( cface != NULL )
    {
        cface->setHIntensity( horizontale );
        cface->setVIntensity( verticale );
    }
}

void LabViewModule::updateComponents()
{

}


