// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file pwm.c
 *
 * @brief This module configures and enables the PWM Module 
 * 
 * Definitions in the file are for dsPIC33CK64MC105 MC DIM plugged onto 
 * Motor Control Development board from Microchip
 *
 * Component: PWM
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*******************************************************************************
* SOFTWARE LICENSE AGREEMENT
* 
* � [2024] Microchip Technology Inc. and its subsidiaries
* 
* Subject to your compliance with these terms, you may use this Microchip 
* software and any derivatives exclusively with Microchip products. 
* You are responsible for complying with third party license terms applicable to
* your use of third party software (including open source software) that may 
* accompany this Microchip software.
* 
* Redistribution of this Microchip software in source or binary form is allowed 
* and must include the above terms of use and the following disclaimer with the
* distribution and accompanying materials.
* 
* SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL 
* MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR 
* CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO
* THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE 
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY
* LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL
* NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS
* SOFTWARE
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
*******************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <xc.h>
#include <stdint.h>
#include "pwm.h"

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="Function Declarations">
void InitPWMGenerator1 (void);
void InitPWMGenerator2 (void);
void InitPWMGenerator3 (void);
void InitPWMGenerator4 (void);
void InitDutyPWM123Generators(void);
void InitPWMGenerators(void);   
void ChargeBootstarpCapacitors(void);


// </editor-fold>
  
// <editor-fold defaultstate="collapsed" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: void InitPWMGenerators(void)  </B>
*
* @brief InitPWMGenerators() function,initializes  and enable the PWM Module 
 * after configuration.
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerators();
 * </code>
*/
void InitPWMGenerators(void)
{

    PCLKCON      = 0x0000;
    /* PWM Clock Divider Selection bits
       0b11 = 1:16 ; 0b10 = 1:8 ;0b01 = 1:4 ; 0b00 = 1:2*/
    PCLKCONbits.DIVSEL = 0;
    /* PWM Master Clock Selection bits
       0b11 = AFPLLO ; 0b10 = FPLLO ; 0b01 = AFVCO/2 ; 0b00 = FOSC */
    PCLKCONbits.MCLKSEL = 0;
    /* Lock bit: 0 = Write-protected registers and bits are unlocked   */
    PCLKCONbits.LOCK = 0;

    /* Initialize Master Phase Register */
    MPHASE       = 0x0000;
    /* Initialize Master Duty Cycle */
    MDC          = 0x0000;
    /* Initialize Master Period Register */
    MPER         = LOOPTIME_TCY;
    
    /* Initialize FREQUENCY SCALE REGISTER*/
    FSCL          = 0x0000;
    /* Initialize FREQUENCY SCALING MINIMUM PERIOD REGISTER */
    FSMINPER     = 0x0000;
    /* Initialize Linear Feedback Shift Register */
    LFSR         = 0x0000;
    /* Initialize Combinational Trigger Register Low */
    CMBTRIGL     = 0x0000;
    /* Initialize Combinational Trigger Register High */
    CMBTRIGH     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER A */
    LOGCONA     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER B*/
    LOGCONB     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER C */
    LOGCONC     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER D */
    LOGCOND     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER E*/
    LOGCONE     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER F */
    LOGCONF     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER A */
    PWMEVTA     = 0x0000;    
    /* PWM EVENT OUTPUT CONTROL REGISTER B */
    PWMEVTB     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER C */
    PWMEVTC     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER D */
    PWMEVTD     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER E */
    PWMEVTE     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER F */
    PWMEVTF     = 0x0000;
    
    /* PWM Event Output Enable bit  
       1 = Event output signal is output on PWMEy pin
       0 = Event output signal is internal only */
    PWMEVTAbits.EVTAOEN  = 0;
    /* EVTyPOL: PWM Event Output Polarity bit
       1 = Event output signal is active-low
       0 = Event output signal is active-high */
    PWMEVTAbits.EVTAPOL  = 0;
    /* EVTySTRD: PWM Event Output Stretch Disable bit
       1 = Event output signal pulse width is not stretched
       0 = Event output signal is stretched to eight PWM clock cycles minimum */
    PWMEVTAbits.EVTASTRD = 1; 
    /* EVTySYNC: PWM Event Output Sync bit
       1 = Event output signal is synchronized to the system clock
       0 = Event output is not synchronized to the system clock
       Event output signal pulse will be two system clocks when this bit is set and EVTySTRD = 1 */
    PWMEVTAbits.EVTASYNC = 1;
    /* EVTySEL[3:0]: PWM Event Selection bits
       1111-1010 = Reserved
       1001 = ADC Trigger 2 signal
       1000 = ADC Trigger 1 signal
       0111 = STEER signal (available in Push-Pull Output modes only)(4)
       0110 = CAHALF signal (available in Center-Aligned modes only)(4)
       0101 = PCI Fault active output signal
       0100 = PCI Current limit active output signal
       0011 = PCI Feed-forward active output signal
       0010 = PCI Sync active output signal
       0001 = PWM Generator output signal(3)
       0000 = Source is selected by the PGTRGSEL[2:0] bits */
    PWMEVTAbits.EVTASEL  = 0b1000;
    /* EVTyPGS[2:0]: PWM Event Source Selection bits
       111-100 = Reserved
       011 = PWM Generator 4
       ...
       000 = PWM Generator 1 */
    PWMEVTAbits.EVTAPGS  = 0b011;
        
    InitPWMGenerator1 ();
    InitPWMGenerator2 ();
    InitPWMGenerator3 ();
    InitPWMGenerator4 ();
    
    InitDutyPWM123Generators();

    IFS4bits.PWM1IF = 0;
    IEC4bits.PWM1IE = 1;
    IPC16bits.PWM1IP = 7;
    
	PG2CONLbits.ON = 1;      // Enable PWM module after initializing generators
    PG3CONLbits.ON = 1;      // Enable PWM module after initializing generators
    PG1CONLbits.ON = 1;      // Enable PWM module after initializing generators
    PG4CONLbits.ON = 1;      // Enable PWM module after initializing generators

    /* Function call to charge Bootstrap capacitors*/
    ChargeBootstarpCapacitors();
}
// *****************************************************************************
/* Function:
    InitDutyPWM123Generators()

  Summary:
    Routine to initialize Duty cycle of PWM generators 1,2,3 

  Description:
    Function initializes Duty cycle of PWM module for 3-phase inverter control 
    in Complimentary mode 

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void InitDutyPWM123Generators(void)
{

// Enable PWMs only on PWMxL ,to charge bootstrap capacitors initially.
    // Hence PWMxH is over-ridden to "LOW"
   
    PG3IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM3H,L, if Override is Enabled
    PG2IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM2H,L, if Override is Enabled
    PG1IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM1H,L, if Override is Enabled

    PG3IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM3H
    PG2IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM2H
    PG1IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM1H

    PG3IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM3L pin
    PG2IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM2L pin
    PG1IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM1L pin

    /* Set PWM Duty Cycles */
    PG3DC = 0;
    PG2DC = 0;      
    PG1DC = 0;

}

// *****************************************************************************
/* Function:
    Charge_Bootstrap_Capacitors()

  Summary:
    Routine to initialize PWM generators 1-3 to charge bootstrap capacitors

  Description:
    Function to charge bootstrap capacitors at the beginning

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void ChargeBootstarpCapacitors(void)
{
    uint16_t i = BOOTSTRAP_CHARGING_COUNTS;
    uint16_t prevStatusCAHALF = 0,currStatusCAHALF = 0;
    uint16_t k = 0;
    
    // Enable PWMs only on PWMxL ,to charge bootstrap capacitors at the beginning
    // Hence PWMxH is over-ridden to "LOW"
    PG3IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM3H,L, if Override is Enabled
    PG2IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM2H,L, if Override is Enabled
    PG1IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM1H,L, if Override is Enabled

    PG3IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM3H
    PG2IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM2H
    PG1IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM1H

    PG3IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM3L
    PG2IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM2L
    PG1IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM1L

    // PDCx: PWMx GENERATOR DUTY CYCLE REGISTER
    // Initialize the PWM duty cycle for charging
    MC1_PWM_PDC3 = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    MC1_PWM_PDC2 = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    MC1_PWM_PDC1 = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    
    while(i)
    {
        prevStatusCAHALF = currStatusCAHALF;
        currStatusCAHALF = PG1STATbits.CAHALF;
        if(prevStatusCAHALF != currStatusCAHALF)
        {
            if(currStatusCAHALF == 0)
            {
                i--; 
                k++;
                if(i == (BOOTSTRAP_CHARGING_COUNTS - 50))
                {
                    // 0 = PWM generator provides data for PWM1L pin
                    PG1IOCONLbits.OVRENL = 0;
                }
                else if(i == (BOOTSTRAP_CHARGING_COUNTS - 150))
                {
                    // 0 = PWM generator provides data for PWM2L pin
                    PG2IOCONLbits.OVRENL = 0;  
                }
                else if(i == (BOOTSTRAP_CHARGING_COUNTS - 250))
                {
                    // 0 = PWM generator provides data for PWM3L pin
                    PG3IOCONLbits.OVRENL = 0;  
                }
                if(k > 25)
                {
                    if(PG3IOCONLbits.OVRENL == 0)
                    {
                        if(MC1_PWM_PDC3 > 2)
                        {
                            MC1_PWM_PDC3 -= 2;
                        }
                        else
                        {
                           MC1_PWM_PDC3 = 0; 
                        }
                    }
                    if(PG2IOCONLbits.OVRENL == 0)
                    {
                        if(MC1_PWM_PDC2 > 2)
                        {
                            MC1_PWM_PDC2 -= 2;
                        }
                        else
                        {
                            MC1_PWM_PDC2 = 0; 
                        }
                    }
                    if(PG1IOCONLbits.OVRENL == 0)
                    {
                        if(MC1_PWM_PDC1 > 2)
                        {
                            MC1_PWM_PDC1 -= 2;
                        }
                        else
                        {
                            MC1_PWM_PDC1 = 0; 
                        }
                    }
                    k = 0;
                } 
            }
        }
    }

    // PDCx: PWMx GENERATOR DUTY CYCLE REGISTER
    // Initialize the PWM duty cycle for charging
    MC1_PWM_PDC3 = 0;
    MC1_PWM_PDC2 = 0;
    MC1_PWM_PDC1 = 0;

    PG3IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM3H pin
    PG2IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM2H pin
    PG1IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM1H pin
}
// *****************************************************************************
/* Function:
    InitPWM1Generator()

  Summary:
    Routine to initialize PWM generators 1 

  Description:
    Function initializes PWM module for 3-phase inverter control in Complimentary
    mode ;initializes period,dead time;Configures PWM fault control logic

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void InitPWMGenerator1 (void)
{

    /* Initialize PWM GENERATOR 1 CONTROL REGISTER LOW */
    PG1CONL      = 0x0000;
    /* PWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG1CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG1CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG1CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG1CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 1 CONTROL REGISTER HIGH */
    PG1CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG1DC
       0 = Macro uses the PG1DC register*/
    PG1CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG1PER
       0 = Macro uses the PG1PER register */
    PG1CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG1PHASE
       0 = Macro uses the PG1PHASE register */
    PG1CONHbits.MPHSEL = 1;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG1CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       000 = SOC update
       Data registers at start of next PWM cycle if UPDREQ = 1. */
    PG1CONHbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode
     * 0b01 = PWM Generator operates in Retriggerable mode */
    PG1CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC
       0100 = Trigger output selected by PG4 PGTRGSEL[2:0] bits (PGxEVTL[2:0])
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG1CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 1 STATUS REGISTER*/
    PG1STAT      = 0x0000;
    /* Initialize PWM GENERATOR 1 I/O CONTROL REGISTER LOW */
    PG1IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG1IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM1H and PWM1L Device Pins bit 
       0 = PWM1H/L signals are mapped to their respective pins */
    PG1IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM1H Pin bit
       0 = PWM Generator provides data for the PWM1H pin*/
    PG1IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM1L Pin bit
       0 = PWM Generator provides data for the PWM1L pin*/
    PG1IOCONLbits.OVRENL = 0;
    /* Data for PWM1H/PWM1L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM1H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM1L */
    PG1IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG1IOCONLbits.OSYNC = 0;
    /* Data for PWM1H/PWM1L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM1H.
       If Fault is active, then FLTDAT<0> provides data for PWM1L.*/
    PG1IOCONLbits.FLTDAT = 0;
    /* Data for PWM1H/PWM1L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM1H.
       If current limit is active, then CLDAT<0> provides data for PWM1L.*/
    PG1IOCONLbits.CLDAT = 0;
    /* Data for PWM1H/PWM1L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM1H.
       If feed-forward is active, then FFDAT<0> provides data for PWM1L.*/
    PG1IOCONLbits.FFDAT = 0;
    /* Data for PWM1H/PWM1L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM1H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM1L data. */
    PG1IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 1 I/O CONTROL REGISTER HIGH */    
    PG1IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG1IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG1IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG1IOCONHbits.PMOD = 0;
    /* PWM1H Output Port Enable bit
       1 = PWM Generator controls the PWM1H output pin
       0 = PWM Generator does not control the PWM1H output pin */
    PG1IOCONHbits.PENH = 1;
    /* PWM1L Output Port Enable bit
       1 = PWM Generator controls the PWM1L output pin
       0 = PWM Generator does not control the PWM1L output pin */
    PG1IOCONHbits.PENL = 1;
    /* PWM1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG1IOCONHbits.POLH = 0;
    /* PWM1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG1IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 1 EVENT REGISTER LOW*/
    PG1EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG1EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG1TRIGC Compare Event Enable bit
       0 = PG1TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG1EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG1TRIGB Compare Event Enable bit
       0 = PG1TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG1EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG1TRIGA Compare Event Enable bit
       1 = PG1TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG1EVTLbits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG1DC register automatically sets the UPDATE bit*/
    PG1EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG1EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 1 EVENT REGISTER HIGH */
    PG1EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG1EVTHbits.FLTIEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG1EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG1EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG1EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG1EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 2 Source is PG1TRIGC Compare Event Enable bit
       0 = PG1TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG1TRIGB Compare Event Enable bit
       0 = PG1TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG1TRIGA Compare Event Enable bit
       0 = PG1TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG1EVTHbits.ADTR1OFS = 0;
    
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG1FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG1FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG1FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG1FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG1FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG1FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG1FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG1FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG1FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG1FPCILbits.PSS = 19;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG1FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG1FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG1FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG1FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG1FPCIHbits.LATMOD  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG1FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG1FPCIHbits.TQSS  = 0;
#endif    

    /* PWM GENERATOR 1 Current Limit PCI REGISTER LOW */
    PG1CLPCIL    = 0x0000;
    /* PWM GENERATOR 1 Current Limit PCI REGISTER HIGH */
    PG1CLPCIH    = 0x0000;
    /* PWM GENERATOR 1 Feed Forward PCI REGISTER LOW */
    PG1FFPCIL    = 0x0000;
    /* PWM GENERATOR 1 Feed Forward  PCI REGISTER HIGH */
    PG1FFPCIH    = 0x0000;
    /* PWM GENERATOR 1 Sync PCI REGISTER LOW */
    PG1SPCIL     = 0x0000;  
    /* TSYNCDIS: Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG1SPCILbits.TSYNCDIS = 1;
    /* TERM[2:0]: Termination Event Selection bits
       111 = Selects PCI Source #9
       110 = Selects PCI Source #8
       101 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI[2:0] bits)
       100 = PGxTRIGC trigger event
       011 = PGxTRIGB trigger event
       010 = PGxTRIGA trigger event
       001 = Auto-Terminate: Terminate when PCI source transitions from active to inactive
       000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location */
    PG1SPCILbits.TERM = 1;
    /* AQPS: Acceptance Qualifier Polarity Select bit
       1 = Inverted
       0 = Not inverted */
    PG1SPCILbits.AQPS = 0;
    /* AQSS[2:0]: Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?0?)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI[2:0] bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No acceptance qualifier is used (qualifier forced to ?1?) */    
    PG1SPCILbits.AQSS = 0;
    /* PSYNC: PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC */
    PG1SPCILbits.PSYNC = 0;
    /* PPS: PCI Polarity Select bit
       1 = Inverted
       0 = Not inverted */
    PG1SPCILbits.PPS = 0;
    /* PSS[4:0]: PCI Source Selection bits
       11111 = CLC1
       11110-11100 = Reserved
       11011 = Comparator 1 output
       11010 = PWM Event D
       11001 = PWM Event C
       11000 = PWM Event B
       10111 = PWM Event A
       10110-10100 = Reserved
       10011 = Device pin, PCI[19]
       10010 = RPn input, PCI18R
       10001 = RPn input, PCI17R
       10000 = RPn input, PCI16R
       01111 = RPn input, PCI15R
       01110 = RPn input, PCI14R
       01101 = RPn input, PCI13R
       01100 = RPn input, PCI12R
       01011 = RPn input, PCI11R
       01010 = RPn input, PCI10R
       01001 = RPn input, PCI9R
       01000 = RPn input, PCI8R
       00100-00111 = Reserved
       00011 = Internally connected to Combo Trigger B
       00010 = Internally connected to Combo Trigger A
       00001 = Internally connected to the output of PWMPCI[2:0] MUX
       00000 = Tied to ?0? */
    PG1SPCILbits.PSS = 0b10111;
    
    /* PWM GENERATOR 1 Sync PCI REGISTER LOW */
    PG1SPCIH     = 0x0000;
    /* Initialize PWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER LOW */
    PG1LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG1LEBH      = 0x0000;
    
    /* Initialize PWM GENERATOR 1 PHASE REGISTER */
    PG1PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 1 DUTY CYCLE REGISTER */
    PG1DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 1 DUTY CYCLE ADJUSTMENT REGISTER */
    PG1DCA       = 0x0000;
    /* Initialize PWM GENERATOR 1 PERIOD REGISTER */
    PG1PER       = 0x0000;
    /* Initialize PWM GENERATOR 1 DEAD-TIME REGISTER LOW */
    PG1DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 1 DEAD-TIME REGISTER HIGH */
    PG1DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 1 TRIGGER A REGISTER */
    PG1TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 1 TRIGGER B REGISTER */
    PG1TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 1 TRIGGER C REGISTER */
    PG1TRIGC     = 0x0000;
    
}
    
// *****************************************************************************
/* Function:
    InitPWMGenerator2()

  Summary:
    Routine to initialize PWM generators 2 

  Description:
    Function initializes PWM module for 3-phase inverter control in Complimentary
    mode ;initializes period,dead time;Configures PWM fault control logic

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void InitPWMGenerator2 (void)
{

    /* Initialize PWM GENERATOR 2 CONTROL REGISTER LOW */
    PG2CONL      = 0x0000;
    /* PWM Generator 2 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG2CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG2CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG2CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG2CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 2 CONTROL REGISTER HIGH */
    PG2CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG2DC
       0 = Macro uses the PG2DC register*/
    PG2CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG2PER
       0 = Macro uses the PG2PER register */
    PG2CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG2PHASE
       0 = Macro uses the PG2PHASE register */
    PG2CONHbits.MPHSEL = 1;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG2CONHbits.MSTEN = 0;
     /* PWM Buffer Update Mode Selection bits 
       000 = SOC update
       Data registers at start of next PWM cycle if UPDREQ = 1. */
	PG2CONHbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode
     * 0b01 = PWM Generator operates in Retriggerable mode */
    PG2CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0001 = PWM1 trigger o/p selected by PG1 PGTRGSEL<2:0> bits(PGxEVT<2:0>)
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG2CONHbits.SOCS = 0x1;
    
    /* Clear PWM GENERATOR 2 STATUS REGISTER*/
    PG2STAT      = 0x0000;
    /* Initialize PWM GENERATOR 2 I/O CONTROL REGISTER LOW */
    PG2IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG2IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM2H and PWM2L Device Pins bit 
       0 = PWM2H/L signals are mapped to their respective pins */
    PG2IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM2H Pin bit
       0 = PWM Generator provides data for the PWM2H pin*/
    PG2IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM2L Pin bit
       0 = PWM Generator provides data for the PWM2L pin*/
    PG2IOCONLbits.OVRENL = 0;
    /* Data for PWM2H/PWM2L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM2H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM2L */
    PG2IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG2IOCONLbits.OSYNC = 0;
    /* Data for PWM2H/PWM2L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM2H.
       If Fault is active, then FLTDAT<0> provides data for PWM2L.*/
    PG2IOCONLbits.FLTDAT = 0;
    /* Data for PWM2H/PWM2L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM2H.
       If current limit is active, then CLDAT<0> provides data for PWM2L.*/
    PG2IOCONLbits.CLDAT = 0;
    /* Data for PWM2H/PWM2L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM2H.
       If feed-forward is active, then FFDAT<0> provides data for PWM2L.*/
    PG2IOCONLbits.FFDAT = 0;
    /* Data for PWM2H/PWM2L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM2H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM2L data. */
    PG2IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 2 I/O CONTROL REGISTER HIGH */    
    PG2IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG2IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG2IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG2IOCONHbits.PMOD = 0;
    /* PWM2H Output Port Enable bit
       1 = PWM Generator controls the PWM2H output pin
       0 = PWM Generator does not control the PWM2H output pin */
    PG2IOCONHbits.PENH = 1;
    /* PWM2L Output Port Enable bit
       1 = PWM Generator controls the PWM2L output pin
       0 = PWM Generator does not control the PWM2L output pin */
    PG2IOCONHbits.PENL = 1;
    /* PWM2H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG2IOCONHbits.POLH = 0;
    /* PWM2L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG2IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 2 EVENT REGISTER LOW*/
    PG2EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG2EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG2TRIGC Compare Event Enable bit
       0 = PG2TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG2TRIGB Compare Event Enable bit
       0 = PG2TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG2TRIGA Compare Event Enable bit
       0 = PG2TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG2DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG2EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG2EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 2 EVENT REGISTER HIGH */
    PG2EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG2EVTHbits.FLTIEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG2EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG2EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG2EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG2EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 2 Source is PG2TRIGC Compare Event Enable bit
       0 = PG2TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG2TRIGB Compare Event Enable bit
       0 = PG2TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG2TRIGA Compare Event Enable bit
       0 = PG2TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG2EVTHbits.ADTR1OFS = 0;
    
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG2FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG2FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG2FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG2FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG2FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG2FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG2FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG2FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG2FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG2FPCILbits.PSS = 19;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG2FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG2FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG2FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG2FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG2FPCIHbits.LATMOD  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG2FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG2FPCIHbits.TQSS  = 0;
#endif
    
    /* PWM GENERATOR 2 Current Limit PCI REGISTER LOW */
    PG2CLPCIL    = 0x0000;
    /* PWM GENERATOR 2 Current Limit PCI REGISTER HIGH */
    PG2CLPCIH    = 0x0000;
    /* PWM GENERATOR 2 Feed Forward PCI REGISTER LOW */
    PG2FFPCIL    = 0x0000;
    /* PWM GENERATOR 2 Feed Forward  PCI REGISTER HIGH */
    PG2FFPCIH    = 0x0000;
    /* PWM GENERATOR 2 Sync PCI REGISTER LOW */
    PG2SPCIL     = 0x0000;
//        /* TSYNCDIS: Termination Synchronization Disable bit
//       1 = Termination of latched PCI occurs immediately
//       0 = Termination of latched PCI occurs at PWM EOC */
//    PG2SPCILbits.TSYNCDIS = 1;
//    /* TERM[2:0]: Termination Event Selection bits
//       111 = Selects PCI Source #9
//       110 = Selects PCI Source #8
//       101 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI[2:0] bits)
//       100 = PGxTRIGC trigger event
//       011 = PGxTRIGB trigger event
//       010 = PGxTRIGA trigger event
//       001 = Auto-Terminate: Terminate when PCI source transitions from active to inactive
//       000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location */
//    PG2SPCILbits.TERM = 1;
//    /* AQPS: Acceptance Qualifier Polarity Select bit
//       1 = Inverted
//       0 = Not inverted */
//    PG2SPCILbits.AQPS = 0;
//    /* AQSS[2:0]: Acceptance Qualifier Source Selection bits
//       111 = SWPCI control bit only (qualifier forced to ?0?)
//       110 = Selects PCI Source #9
//       101 = Selects PCI Source #8
//       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI[2:0] bits)
//       011 = PWM Generator is triggered
//       010 = LEB is active
//       001 = Duty cycle is active (base PWM Generator signal)
//       000 = No acceptance qualifier is used (qualifier forced to ?1?) */    
//    PG2SPCILbits.AQSS = 0;
//    /* PSYNC: PCI Synchronization Control bit
//       1 = PCI source is synchronized to PWM EOC
//       0 = PCI source is not synchronized to PWM EOC */
//    PG2SPCILbits.PSYNC = 0;
//    /* PPS: PCI Polarity Select bit
//       1 = Inverted
//       0 = Not inverted */
//    PG2SPCILbits.PPS = 0;
//    /* PSS[4:0]: PCI Source Selection bits
//       11111 = CLC1
//       11110-11100 = Reserved
//       11011 = Comparator 1 output
//       11010 = PWM Event D
//       11001 = PWM Event C
//       11000 = PWM Event B
//       10111 = PWM Event A
//       10110-10100 = Reserved
//       10011 = Device pin, PCI[19]
//       10010 = RPn input, PCI18R
//       10001 = RPn input, PCI17R
//       10000 = RPn input, PCI16R
//       01111 = RPn input, PCI15R
//       01110 = RPn input, PCI14R
//       01101 = RPn input, PCI13R
//       01100 = RPn input, PCI12R
//       01011 = RPn input, PCI11R
//       01010 = RPn input, PCI10R
//       01001 = RPn input, PCI9R
//       01000 = RPn input, PCI8R
//       00100-00111 = Reserved
//       00011 = Internally connected to Combo Trigger B
//       00010 = Internally connected to Combo Trigger A
//       00001 = Internally connected to the output of PWMPCI[2:0] MUX
//       00000 = Tied to ?0? */
//    PG2SPCILbits.PSS = 0b10111;
    /* PWM GENERATOR 2 Sync PCI REGISTER LOW */
    PG2SPCIH     = 0x0000;
    
    /* Initialize PWM GENERATOR 2 LEADING-EDGE BLANKING REGISTER LOW */
    PG2LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 2 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG2LEBH      = 0x0000;
    
    /* Initialize PWM GENERATOR 2 PHASE REGISTER */
    PG2PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 2 DUTY CYCLE REGISTER */
    PG2DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 2 DUTY CYCLE ADJUSTMENT REGISTER */
    PG2DCA       = 0x0000;
    /* Initialize PWM GENERATOR 2 PERIOD REGISTER */
    PG2PER       = 0x0000;
    /* Initialize PWM GENERATOR 2 DEAD-TIME REGISTER LOW */
    PG2DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 2 DEAD-TIME REGISTER HIGH */
    PG2DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 2 TRIGGER A REGISTER */
    PG2TRIGA     = 0x0000;
    /* Initialize PWM GENERATOR 2 TRIGGER B REGISTER */
    PG2TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 2 TRIGGER C REGISTER */
    PG2TRIGC     = 0x0000;
    
}
    
// *****************************************************************************
/* Function:
    InitPWMGenerator3()

  Summary:
    Routine to initialize PWM generators 3 

  Description:
    Function initializes PWM module for 3-phase inverter control in Complimentary
    mode ;initializes period,dead time;Configures PWM fault control logic

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void InitPWMGenerator3 (void)
{

    /* Initialize PWM GENERATOR 3 CONTROL REGISTER LOW */
    PG3CONL      = 0x0000;
    /* PWM Generator 3 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG3CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG3CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG3CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG3CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 3 CONTROL REGISTER HIGH */
    PG3CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG3DC
       0 = Macro uses the PG3DC register*/
    PG3CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG3PER
       0 = Macro uses the PG3PER register */
    PG3CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG3PHASE
       0 = Macro uses the PG3PHASE register */
    PG3CONHbits.MPHSEL = 1;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG3CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       000 = SOC update
        Data registers at start of next PWM cycle if UPDREQ = 1.*/
	PG3CONHbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode
     * 0b01 = PWM Generator operates in Retriggerable mode */
    PG3CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0001 = PWM1 trigger o/p selected by PG1 PGTRGSEL<2:0> bits(PGxEVT<2:0>)
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG3CONHbits.SOCS = 0x1;
    
    /* Clear PWM GENERATOR 3 STATUS REGISTER*/
    PG3STAT      = 0x0000;
    /* Initialize PWM GENERATOR 3 I/O CONTROL REGISTER LOW */
    PG3IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG3IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM3H and PWM3L Device Pins bit 
       0 = PWM3H/L signals are mapped to their respective pins */
    PG3IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM3H Pin bit
       0 = PWM Generator provides data for the PWM3H pin*/
    PG3IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM3L Pin bit
       0 = PWM Generator provides data for the PWM3L pin*/
    PG3IOCONLbits.OVRENL = 0;
    /* Data for PWM3H/PWM3L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM3H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM3L */
    PG3IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG3IOCONLbits.OSYNC = 0;
    /* Data for PWM3H/PWM3L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM3H.
       If Fault is active, then FLTDAT<0> provides data for PWM3L.*/
    PG3IOCONLbits.FLTDAT = 0;
    /* Data for PWM3H/PWM3L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM3H.
       If current limit is active, then CLDAT<0> provides data for PWM3L.*/
    PG3IOCONLbits.CLDAT = 0;
    /* Data for PWM3H/PWM3L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM3H.
       If feed-forward is active, then FFDAT<0> provides data for PWM3L.*/
    PG3IOCONLbits.FFDAT = 0;
    /* Data for PWM3H/PWM3L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM3H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM3L data. */
    PG3IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 3 I/O CONTROL REGISTER HIGH */    
    PG3IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG3IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG3IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG3IOCONHbits.PMOD = 0;
    /* PWM3H Output Port Enable bit
       1 = PWM Generator controls the PWM3H output pin
       0 = PWM Generator does not control the PWM3H output pin */
    PG3IOCONHbits.PENH = 1;
    /* PWM3L Output Port Enable bit
       1 = PWM Generator controls the PWM3L output pin
       0 = PWM Generator does not control the PWM3L output pin */
    PG3IOCONHbits.PENL = 1;
    /* PWM3H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG3IOCONHbits.POLH = 0;
    /* PWM3L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG3IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 3 EVENT REGISTER LOW*/
    PG3EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG3EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG3TRIGC Compare Event Enable bit
       0 = PG3TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG3TRIGB Compare Event Enable bit
       0 = PG3TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG3TRIGA Compare Event Enable bit
       0 = PG3TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG3DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG3EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG3EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 3 EVENT REGISTER HIGH */
    PG3EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG3EVTHbits.FLTIEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG3EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG3EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG3EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG3EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 3 Source is PG3TRIGC Compare Event Enable bit
       0 = PG3TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG3TRIGB Compare Event Enable bit
       0 = PG3TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG3TRIGA Compare Event Enable bit
       0 = PG3TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG3EVTHbits.ADTR1OFS = 0;
    
    /* PWM GENERATOR 3 Fault PCI REGISTER LOW */
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG3FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG3FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG3FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG3FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG3FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG3FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG3FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG3FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG3FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG3FPCILbits.PSS = 19;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG3FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG3FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG3FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG3FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG3FPCIHbits.LATMOD  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG3FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG3FPCIHbits.TQSS  = 0;
#endif
    
    /* PWM GENERATOR 3 Current Limit PCI REGISTER LOW */
    PG3CLPCIL    = 0x0000;
    /* PWM GENERATOR 3 Current Limit PCI REGISTER HIGH */
    PG3CLPCIH    = 0x0000;
    /* PWM GENERATOR 3 Feed Forward PCI REGISTER LOW */
    PG3FFPCIL    = 0x0000;
    /* PWM GENERATOR 3 Feed Forward  PCI REGISTER HIGH */
    PG3FFPCIH    = 0x0000;
    /* PWM GENERATOR 3 Sync PCI REGISTER LOW */
    PG3SPCIL     = 0x0000;
//        /* TSYNCDIS: Termination Synchronization Disable bit
//       1 = Termination of latched PCI occurs immediately
//       0 = Termination of latched PCI occurs at PWM EOC */
//    PG3SPCILbits.TSYNCDIS = 1;
//    /* TERM[2:0]: Termination Event Selection bits
//       111 = Selects PCI Source #9
//       110 = Selects PCI Source #8
//       101 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI[2:0] bits)
//       100 = PGxTRIGC trigger event
//       011 = PGxTRIGB trigger event
//       010 = PGxTRIGA trigger event
//       001 = Auto-Terminate: Terminate when PCI source transitions from active to inactive
//       000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location */
//    PG3SPCILbits.TERM = 1;
//    /* AQPS: Acceptance Qualifier Polarity Select bit
//       1 = Inverted
//       0 = Not inverted */
//    PG3SPCILbits.AQPS = 0;
//    /* AQSS[2:0]: Acceptance Qualifier Source Selection bits
//       111 = SWPCI control bit only (qualifier forced to ?0?)
//       110 = Selects PCI Source #9
//       101 = Selects PCI Source #8
//       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI[2:0] bits)
//       011 = PWM Generator is triggered
//       010 = LEB is active
//       001 = Duty cycle is active (base PWM Generator signal)
//       000 = No acceptance qualifier is used (qualifier forced to ?1?) */    
//    PG3SPCILbits.AQSS = 0;
//    /* PSYNC: PCI Synchronization Control bit
//       1 = PCI source is synchronized to PWM EOC
//       0 = PCI source is not synchronized to PWM EOC */
//    PG3SPCILbits.PSYNC = 0;
//    /* PPS: PCI Polarity Select bit
//       1 = Inverted
//       0 = Not inverted */
//    PG3SPCILbits.PPS = 0;
//    /* PSS[4:0]: PCI Source Selection bits
//       11111 = CLC1
//       11110-11100 = Reserved
//       11011 = Comparator 1 output
//       11010 = PWM Event D
//       11001 = PWM Event C
//       11000 = PWM Event B
//       10111 = PWM Event A
//       10110-10100 = Reserved
//       10011 = Device pin, PCI[19]
//       10010 = RPn input, PCI18R
//       10001 = RPn input, PCI17R
//       10000 = RPn input, PCI16R
//       01111 = RPn input, PCI15R
//       01110 = RPn input, PCI14R
//       01101 = RPn input, PCI13R
//       01100 = RPn input, PCI12R
//       01011 = RPn input, PCI11R
//       01010 = RPn input, PCI10R
//       01001 = RPn input, PCI9R
//       01000 = RPn input, PCI8R
//       00100-00111 = Reserved
//       00011 = Internally connected to Combo Trigger B
//       00010 = Internally connected to Combo Trigger A
//       00001 = Internally connected to the output of PWMPCI[2:0] MUX
//       00000 = Tied to ?0? */
//    PG3SPCILbits.PSS = 0b10111;
    /* PWM GENERATOR 3 Sync PCI REGISTER LOW */
    PG3SPCIH     = 0x0000;
    
    /* Initialize PWM GENERATOR 3 LEADING-EDGE BLANKING REGISTER LOW */
    PG3LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 3 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG3LEBH      = 0x0000;
    
    /* Initialize PWM GENERATOR 3 PHASE REGISTER */
    PG3PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 3 DUTY CYCLE REGISTER */
    PG3DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 3 DUTY CYCLE ADJUSTMENT REGISTER */
    PG3DCA       = 0x0000;
    /* Initialize PWM GENERATOR 3 PERIOD REGISTER */
    PG3PER       = 0x0000;
    /* Initialize PWM GENERATOR 3 DEAD-TIME REGISTER LOW */
    PG3DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 3 DEAD-TIME REGISTER HIGH */
    PG3DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 3 TRIGGER A REGISTER */
    PG3TRIGA     = 0x0000;
    /* Initialize PWM GENERATOR 3 TRIGGER B REGISTER */
    PG3TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 3 TRIGGER C REGISTER */
    PG3TRIGC     = 0x0000;
    
}

void InitPWMGenerator4 (void)
{

    /* Initialize PWM GENERATOR 4 CONTROL REGISTER LOW */
    PG4CONL      = 0x0000;
    /* PWM Generator 4 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG4CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG4CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG4CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG4CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 4 CONTROL REGISTER HIGH */
    PG4CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG4DC
       0 = Macro uses the PG4DC register*/
    PG4CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG4PER
       0 = Macro uses the PG4PER register */
    PG4CONHbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG4PHASE
       0 = Macro uses the PG4PHASE register */
    PG4CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG4CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       000 = SOC update
        Data registers at start of next PWM cycle if UPDREQ = 1.*/
	PG4CONHbits.UPDMOD = 0b000;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG4CONHbits.TRGMOD = 0;
    /* Start of Cycle Selection bits
       0000 = Local EOC
       0100 = Trigger output selected by PG4 PGTRGSEL[2:0] bits (PGxEVTL[2:0])
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG4CONHbits.SOCS = 0;
    
    /* Clear PWM GENERATOR 4 STATUS REGISTER*/
    PG4STAT      = 0x0000;
    /* Initialize PWM GENERATOR 4 I/O CONTROL REGISTER LOW */
    PG4IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG4IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM4H and PWM4L Device Pins bit 
       0 = PWM4H/L signals are mapped to their respective pins */
    PG4IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM4H Pin bit
       0 = PWM Generator provides data for the PWM4H pin*/
    PG4IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM4L Pin bit
       0 = PWM Generator provides data for the PWM4L pin*/
    PG4IOCONLbits.OVRENL = 0;
    /* Data for PWM4H/PWM4L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM4H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM4L */
    PG4IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG4IOCONLbits.OSYNC = 0;
    /* Data for PWM4H/PWM4L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM4H.
       If Fault is active, then FLTDAT<0> provides data for PWM4L.*/
    PG4IOCONLbits.FLTDAT = 0;
    /* Data for PWM4H/PWM4L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM4H.
       If current limit is active, then CLDAT<0> provides data for PWM4L.*/
    PG4IOCONLbits.CLDAT = 0;
    /* Data for PWM4H/PWM4L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM4H.
       If feed-forward is active, then FFDAT<0> provides data for PWM4L.*/
    PG4IOCONLbits.FFDAT = 0;
    /* Data for PWM4H/PWM4L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM4H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM4L data. */
    PG4IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 4 I/O CONTROL REGISTER HIGH */    
    PG4IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG4IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG4IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       01 = PWM Generator outputs operate in Independent mode
       00 = PWM Generator outputs operate in Complementary mode*/
    PG4IOCONHbits.PMOD = 1;
    /* PWM4H Output Port Enable bit
       1 = PWM Generator controls the PWM4H output pin
       0 = PWM Generator does not control the PWM4H output pin */
    PG4IOCONHbits.PENH = 1;
    /* PWM4L Output Port Enable bit
       1 = PWM Generator controls the PWM4L output pin
       0 = PWM Generator does not control the PWM4L output pin */
    PG4IOCONHbits.PENL = 0;
    /* PWM4H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG4IOCONHbits.POLH = 0;
    /* PWM4L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG4IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 4 EVENT REGISTER LOW*/
    PG4EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       0b0000 = 1:1 
       0b0011 = 1:4 */
    PG4EVTLbits.ADTR1PS = 0b0011;
    /* ADC Trigger 1 Source is PG4TRIGC Compare Event Enable bit
       0 = PG4TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG4EVTLbits.ADTR1EN3  = 1;
    /* ADC Trigger 1 Source is PG4TRIGB Compare Event Enable bit
       0 = PG4TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG4EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG4TRIGA Compare Event Enable bit
       0 = PG4TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG4EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG4DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG4EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger
       011 = PGxTRIGC compare event is the PWM Generator trigger*/
    PG4EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 4 EVENT REGISTER HIGH */
    PG4EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG4EVTHbits.FLTIEN = 0;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG4EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG4EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG4EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG4EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 2 Source is PG4TRIGC Compare Event Enable bit
       0 = PG4TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG4EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG4TRIGB Compare Event Enable bit
       0 = PG4TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG4EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG4TRIGA Compare Event Enable bit
       0 = PG4TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG4EVTHbits.ADTR2EN1 = 1;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG4EVTHbits.ADTR1OFS = 0;
    
    /* PWM GENERATOR 4 Fault PCI REGISTER LOW */
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 4 Fault PCI REGISTER LOW */
    PG4FPCIL     = 0x0000;
    /* PWM GENERATOR 4 Fault PCI REGISTER HIGH */
    PG4FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 4 Fault PCI REGISTER LOW */
    PG4FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG4FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG4FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG4FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG4FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG4FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG4FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG4FPCILbits.PSS = 19;
    
    /* PWM GENERATOR 4 Fault PCI REGISTER HIGH */
    PG4FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG4FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG4FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG4FPCIHbits.ACP   = 0;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG4FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG4FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG4FPCIHbits.TQSS  = 3;
#endif
    
    /* PWM GENERATOR 4 Current Limit PCI REGISTER LOW */
    PG4CLPCIL    = 0x0000;
    /* PWM GENERATOR 4 Current Limit PCI REGISTER HIGH */
    PG4CLPCIH    = 0x0000;
    /* PWM GENERATOR 4 Feed Forward PCI REGISTER LOW */
    PG4FFPCIL    = 0x0000;
    /* PWM GENERATOR 4 Feed Forward  PCI REGISTER HIGH */
    PG4FFPCIH    = 0x0000;
    /* PWM GENERATOR 4 Sync PCI REGISTER LOW */
    PG4SPCIL     = 0x0000;
    /* PWM GENERATOR 4 Sync PCI REGISTER LOW */
    PG4SPCIH     = 0x0000;
    
    /* Initialize PWM GENERATOR 4 LEADING-EDGE BLANKING REGISTER LOW */
    PG4LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 4 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG4LEBH      = 0x0000;
    
    /* Initialize PWM GENERATOR 4 PHASE REGISTER */
    PG4PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 4 DUTY CYCLE REGISTER */
    PG4DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 4 DUTY CYCLE ADJUSTMENT REGISTER */
    PG4DCA       = 0x0000;
    /* Initialize PWM GENERATOR 4 PERIOD REGISTER */
    PG4PER       = PFC_LOOPTIME_TCY;
    /* Initialize PWM GENERATOR 4 DEAD-TIME REGISTER LOW */
    PG4DTL       = 0x0000;
    /* Initialize PWM GENERATOR 4 DEAD-TIME REGISTER HIGH */
    PG4DTH       = 0x0000;

    /* Initialize PWM GENERATOR 4 TRIGGER A REGISTER */
    PG4TRIGA     = PFC_ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 4 TRIGGER B REGISTER */
    PG4TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 4 TRIGGER C REGISTER */
    PG4TRIGC     = PFC_Sync_MC_Value;
}
// </editor-fold> 
