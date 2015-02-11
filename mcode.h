#ifndef MCODE_H
#define MCODE_H

namespace MCode {
/**
 * @brief The MCodeFlags enum Base value for Polybox M-Code.
 */
enum MCodeFlags
{
    ASK_CNC_UPDATE=600, ASK_PRINTER_UPDATE=630, ASK_LABVIEW_UPDATE=620, ASK_SCANNER_UPDATE=610
};

/**      CNC MCODE    **/

#define MCODE_CNC_TOOL_PLUGGED                  601
#define MCODE_CNC_LUBRICANT_PLUGGED             602
#define MCODE_CNC_LUBRICANT_LEVEL               603
#define MCODE_CNC_VACUUM_DETECTED               604
#define MCODE_CNC_RECYCLE_STATE                 605
#define MCODE_CNC_VACUUM_STATE                  606
#define MCODE_CNC_LUBRICANT_STATE               607

/**      SCANNER MCODE    **/

#define MCODE_SCANNER_TURNTABLE_PLUGGED         621
#define MCODE_SCANNER_GET_LASER_PLUGGED         622
#define MCODE_SCANNER_SET_TURNTABLE_STATE       624
#define MCODE_SCANNER_TURNTABLE_X_STEPS         625
#define MCODE_SCANNER_SET_CLOCK_DIRECTION_TABLE 627
#define MCODE_SCANNER_SET_LASER_STATE           629
#define MCODE_SCANNER_SET_LASER_ROTATION_STATE  631
#define MCODE_SCANNER_LASER_TURN_X_STEPS        632
#define MCODE_SCANNER_SET_CLOCK_DIRECTION_LASER 634

/**      LABVIEW MCODE    **/

#define MCODE_LABVIEW_GET_STATUS                640
#define MCODE_LABVIEW_SET_STATUS                641
#define MCODE_LABVIEW_GET_GLOBAL_RGB            642
#define MCODE_LABVIEW_SET_GLOBAL_RGB            643
#define MCODE_LABVIEW_GET_GLOBAL_I              644
#define MCODE_LABVIEW_SET_GLOBAL_I              645
#define MCODE_LABVIEW_GET_FACE_I                646
#define MCODE_LABVIEW_SET_FACE_I                647
#define MCODE_LABVIEW_LED_PLUGGED               648
#define MCODE_LABVIEW_SET_CONTROLLER            649
#define MCODE_LABVIEW_GET_FACE_RGB              650
#define MCODE_LABVIEW_SET_FACE_RGB              651

/**      PRINTER MCODE    **/

#define MCODE_PRINTER_GET_STATUS                660
#define MCODE_PRINTER_SET_STATUS                661
#define MCODE_PRINTER_TOOL_PLUGGED              662
#define MCODE_PRINTER_WIRE_DETECTED             663
#define MCODE_PRINTER_BED_PLUGGED               664
#define MCODE_PRINTER_PEL_PLUGGED               665
#define MCODE_PRINTER_GET_COOLER_BOX_STATUS     666
#define MCODE_PRINTER_SET_FAN_SPEED             667
#define MCODE_PRINTER_GET_COLDEND_STATUS        668
#define MCODE_PRINTER_GET_BED_TEMP_C            669
#define MCODE_PRINTER_SET_BED_TEMP              670
#define MCODE_PRINTER_SET_BED_TEMP_FAST         671
#define MCODE_PRINTER_SET_ALL_FAN               672
#define MCODE_PRINTER_GET_CHAMBER_TEMP          673
#define MCODE_PRINTER_SET_CHAMBER_TEMP          674
#define MCODE_PRINTER_SET_CHAMBER_FAST          675
#define MCODE_PRINTER_GET_BUSE_CLOGGED          676
#define MCODE_PRINTER_GET_CHAMBER_TEMP_ALL      677

/**      GLOBAL MCODE    **/

#define MCODE_GLOBAL_GET_STATUS                 680
#define MCODE_GLOBAL_SET_STATUS                 681
#define MCODE_GLOBAL_GET_BOX_OPEN               682
#define MCODE_GLOBAL_GET_ARDUINO_DETECTED       683
#define MCODE_GLOBAL_GET_IC_OPEN                684
#define MCODE_GLOBAL_GET_PREASI                 685
#define MCODE_GLOBAL_GET_IC_TEMP                686
#define MCODE_GLOBAL_GET_POWER_STATUS           687
#define MCODE_GLOBAL_GET_TOOL_STATE             688
#define MCODE_GLOBAL_SET_TOOL_STATE             689
#define MCODE_GLOBAL_SET_POWER_STATUS           690
#define MCODE_GLOBAL_SET_PAUSE                  691

#define MCODE_PING_PONG                         703
#define MCODE_END_CONNECTION                    705
#define MCODE_START_CONNECTION                  706

}

#endif // MCODE_H
