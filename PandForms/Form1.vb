Imports System
Imports System.IO


Public Class Form1
    Public activeThread As Boolean = False
    Dim cards(14) As Integer
    Dim playername As String = "Name"
    Dim nP As Integer = 0
    Dim locP(4) As Integer
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        activeThread = True
        NameUpdate.Start()
        PlayerHandThread.RunWorkerAsync()

    End Sub

    Private Sub PlayerHandThread_DoWork(sender As Object, e As System.ComponentModel.DoWorkEventArgs) Handles PlayerHandThread.DoWork
        Dim line As String = ""
        Dim temp As String = ""
        Dim count As Integer = 0
        Dim cardindex As Integer = 0
        Dim tempP As PictureBox = RoleBox
        While activeThread
            Threading.Thread.Sleep(200)
            line = My.Computer.FileSystem.ReadAllText("C:\Pand\hfile.txt") 'PIPED DATA IS READ
            If line.Length > 0 Then
                For index As Integer = 0 To line.Length - 1

                    If Not line(index) = " " Then temp = temp + line(index)
                    If line(index) = " " Then
                        If count = 0 Then
                            playername = temp
                            temp = ""
                            count = count + 1
                        Else
                            cards(count - 1) = Convert.ToInt16(temp)
                            'MsgBox(cards(count - 1))
                            temp = ""
                            count = count + 1
                        End If
                    End If
                Next
                nP = cards(9)
                locP(0) = cards(10)
                locP(1) = cards(11)
                locP(2) = cards(12)
                locP(3) = cards(13)

                Try

                    If cards(0) < -1 Then RoleBox.Image = My.Resources.qm1
                    If cards(0) = 0 Then RoleBox.Image = My.Resources.ContingencyPlanner
                    If cards(0) = 1 Then RoleBox.Image = My.Resources.Dispatcher
                    If cards(0) = 2 Then RoleBox.Image = My.Resources.Medic
                    If cards(0) = 3 Then RoleBox.Image = My.Resources.OperationsExpert
                    If cards(0) = 4 Then RoleBox.Image = My.Resources.QuarantineSpecialist
                    If cards(0) = 5 Then RoleBox.Image = My.Resources.Researcher
                    If cards(0) = 6 Then RoleBox.Image = My.Resources.Scientist

                Catch
                    'Do nothing
                End Try



                For cardindex = 1 To 8
                    'CITY
                    Try
                        If cardindex = 1 Then tempP = PictureBox2
                        If cardindex = 2 Then tempP = PictureBox3
                        If cardindex = 3 Then tempP = PictureBox4
                        If cardindex = 4 Then tempP = PictureBox5
                        If cardindex = 5 Then tempP = PictureBox6
                        If cardindex = 6 Then tempP = PictureBox7
                        If cardindex = 7 Then tempP = PictureBox8
                        If cardindex = 8 Then tempP = Extra

                        If cards(cardindex) = -1 Then tempP.Image = My.Resources.qm1

                        If cards(cardindex) = 0 Then tempP.Image = My.Resources.ALGIERS
                        If cards(cardindex) = 1 Then tempP.Image = My.Resources.ATLANTA
                        If cards(cardindex) = 2 Then tempP.Image = My.Resources.BAGHDAD
                        If cards(cardindex) = 3 Then tempP.Image = My.Resources.BANGKOK
                        If cards(cardindex) = 4 Then tempP.Image = My.Resources.BEIJING
                        If cards(cardindex) = 5 Then tempP.Image = My.Resources.BOGOTA
                        If cards(cardindex) = 6 Then tempP.Image = My.Resources.BUENOSAIRES
                        If cards(cardindex) = 7 Then tempP.Image = My.Resources.CAIRO
                        If cards(cardindex) = 8 Then tempP.Image = My.Resources.CHENNAI
                        If cards(cardindex) = 9 Then tempP.Image = My.Resources.CHICAGO
                        If cards(cardindex) = 10 Then tempP.Image = My.Resources.DELHI
                        If cards(cardindex) = 11 Then tempP.Image = My.Resources.ESSEN
                        If cards(cardindex) = 12 Then tempP.Image = My.Resources.HOCHIMINHCITY
                        If cards(cardindex) = 13 Then tempP.Image = My.Resources.HONGKONG
                        If cards(cardindex) = 14 Then tempP.Image = My.Resources.ISTANBUL
                        If cards(cardindex) = 15 Then tempP.Image = My.Resources.JAKARTA
                        If cards(cardindex) = 16 Then tempP.Image = My.Resources.JOHANNESBURG
                        If cards(cardindex) = 17 Then tempP.Image = My.Resources.KARACHI
                        If cards(cardindex) = 18 Then tempP.Image = My.Resources.KHARTOUM
                        If cards(cardindex) = 19 Then tempP.Image = My.Resources.KINSHASA
                        If cards(cardindex) = 20 Then tempP.Image = My.Resources.KOLKATA
                        If cards(cardindex) = 21 Then tempP.Image = My.Resources.LAGOS
                        If cards(cardindex) = 22 Then tempP.Image = My.Resources.LIMA
                        If cards(cardindex) = 23 Then tempP.Image = My.Resources.LONDON
                        If cards(cardindex) = 24 Then tempP.Image = My.Resources.LOSANGELES
                        If cards(cardindex) = 25 Then tempP.Image = My.Resources.MADRID
                        If cards(cardindex) = 26 Then tempP.Image = My.Resources.MANILA
                        If cards(cardindex) = 27 Then tempP.Image = My.Resources.MEXICOCITY
                        If cards(cardindex) = 28 Then tempP.Image = My.Resources.MIAMI
                        If cards(cardindex) = 29 Then tempP.Image = My.Resources.MILAN
                        If cards(cardindex) = 30 Then tempP.Image = My.Resources.MOSCOW
                        If cards(cardindex) = 31 Then tempP.Image = My.Resources.MUMBAI
                        If cards(cardindex) = 32 Then tempP.Image = My.Resources.NEWYORK
                        If cards(cardindex) = 33 Then tempP.Image = My.Resources.OSAKA
                        If cards(cardindex) = 34 Then tempP.Image = My.Resources.PARIS
                        If cards(cardindex) = 35 Then tempP.Image = My.Resources.RIYADH
                        If cards(cardindex) = 36 Then tempP.Image = My.Resources.SANFRANCISCO
                        If cards(cardindex) = 37 Then tempP.Image = My.Resources.SANTIAGO
                        If cards(cardindex) = 38 Then tempP.Image = My.Resources.SAOPAULO
                        If cards(cardindex) = 39 Then tempP.Image = My.Resources.SEOUL
                        If cards(cardindex) = 40 Then tempP.Image = My.Resources.SHANGHAI
                        If cards(cardindex) = 41 Then tempP.Image = My.Resources.STPETERSBURG
                        If cards(cardindex) = 42 Then tempP.Image = My.Resources.SYDNEY
                        If cards(cardindex) = 43 Then tempP.Image = My.Resources.TAIPEI
                        If cards(cardindex) = 44 Then tempP.Image = My.Resources.TEHRAN
                        If cards(cardindex) = 45 Then tempP.Image = My.Resources.TOKYO
                        If cards(cardindex) = 46 Then tempP.Image = My.Resources.TORONTO
                        If cards(cardindex) = 47 Then tempP.Image = My.Resources.WASHINGTON
                        'EPIDEMIC
                        If cards(cardindex) = 48 Then tempP.Image = My.Resources.VirulentStrain1
                        If cards(cardindex) = 49 Then tempP.Image = My.Resources.VirulentStrain2
                        If cards(cardindex) = 50 Then tempP.Image = My.Resources.VirulentStrain3
                        If cards(cardindex) = 51 Then tempP.Image = My.Resources.VirulentStrain4
                        If cards(cardindex) = 52 Then tempP.Image = My.Resources.VirulentStrain5
                        If cards(cardindex) = 53 Then tempP.Image = My.Resources.VirulentStrain6
                        'EVENT
                        If cards(cardindex) = 54 Then tempP.Image = My.Resources.Airlift
                        If cards(cardindex) = 55 Then tempP.Image = My.Resources.Forecast
                        If cards(cardindex) = 56 Then tempP.Image = My.Resources.GovernmentGrant
                        If cards(cardindex) = 57 Then tempP.Image = My.Resources.OneQuietNight
                        If cards(cardindex) = 58 Then tempP.Image = My.Resources.ResilientPopulation
                    Catch
                        'Do nothing
                    End Try
                Next

            End If
            'MsgBox("TESTDONE")
            count = 0
        End While
    End Sub

    Private Sub NameUpdate_Tick(sender As Object, e As EventArgs) Handles NameUpdate.Tick
        Pname.Text = playername
    End Sub

End Class
