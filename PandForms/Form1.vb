Imports System
Imports System.IO


Public Class Form1
    Dim cards(14) As Integer
    Dim playername As String = "Name"
    Dim nP As Integer = 0
    Dim locP(4) As Integer
    Dim Rc(48) As Integer
    Dim color(48) As Integer
    Dim number(48) As Integer
    Dim lineOld As String = ""
    Dim lineNameOld As String = ""

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        NameUpdate.Start()
        Threading.Thread.Sleep(200)

    End Sub

    
    Private Sub NameUpdate_Tick(sender As Object, e As EventArgs) Handles NameUpdate.Tick
        Try
            Pname.Text = playername
            Dim line As String = ""
            Dim temp As String = ""
            Dim count As Integer = 0
            Dim cardindex As Integer = 0
            Dim tempP As PictureBox = RoleBox

            Try
                line = My.Computer.FileSystem.ReadAllText("C:\Pand\hfile.txt") 'PIPED DATA IS READ
            Catch
                'Do nothing
            End Try




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

            If Not lineNameOld = line Then Me.Refresh()
            lineNameOld = line

            count = 0
            Try
                line = My.Computer.FileSystem.ReadAllText("C:\Pand\citydetails.txt") 'PIPED DATA IS READ
            Catch
                'Do nothing
            End Try


            If (line.Length > 0) Then
                For index As Integer = 0 To 47

                    'READ PIPED DATA FOR CITY DETAILS
                    If line(index) = "1" Then color(index) = 1
                    If line(index) = "2" Then color(index) = 2
                    If line(index) = "3" Then color(index) = 3
                    If line(index) = "4" Then color(index) = 4




                Next
                For index As Integer = 0 To 47
                    If line(index + 48) = "1" Then number(index) = 1
                    If line(index + 48) = "2" Then number(index) = 2
                    If line(index + 48) = "3" Then number(index) = 3
                    If line(index + 48) = "4" Then number(index) = 4


                Next
                For index As Integer = 0 To 47
                    If line(index + 48 + 48) = "1" Then Rc(index) = 1
                    If line(index + 48 + 48) = "0" Then Rc(index) = 0



                Next

            End If
            If Not lineOld = line Then Me.Refresh()
            lineOld = line
        Catch
            'Do nothing
        End Try


    End Sub

    Private Sub Form1_Paint(sender As Object, e As PaintEventArgs) Handles MyBase.Paint
        Dim tempL As Label

        Dim line As String = ""
        Dim temp As String = ""
        Dim count As Integer = 0
        Dim cardindex As Integer = 0
                

        count = 0



        For Int As Integer = 0 To 48
            If Int = 0 Then tempL = Algiers
            If Int = 1 Then tempL = Atlanta
            If Int = 2 Then tempL = Bagdad
            If Int = 3 Then tempL = Bangkok
            If Int = 4 Then tempL = Beijing
            If Int = 5 Then tempL = Bogota
            If Int = 6 Then tempL = BuenosAires
            If Int = 7 Then tempL = Cairo
            If Int = 8 Then tempL = Chennai
            If Int = 9 Then tempL = Chicago
            If Int = 10 Then tempL = Delhi
            If Int = 11 Then tempL = Essen
            If Int = 12 Then tempL = HchCity
            If Int = 13 Then tempL = HongKong
            If Int = 14 Then tempL = Istanbul
            If Int = 15 Then tempL = Jakarta
            If Int = 16 Then tempL = Johannesburg
            If Int = 17 Then tempL = Karachi
            If Int = 18 Then tempL = Khartoum
            If Int = 19 Then tempL = Kinshasa
            If Int = 20 Then tempL = Kolkata
            If Int = 21 Then tempL = Lagos
            If Int = 22 Then tempL = Lima
            If Int = 23 Then tempL = London
            If Int = 24 Then tempL = LA
            If Int = 25 Then tempL = Madrid
            If Int = 26 Then tempL = Manila
            If Int = 27 Then tempL = MexicoCity
            If Int = 28 Then tempL = Miami
            If Int = 29 Then tempL = Milan
            If Int = 30 Then tempL = Moscow
            If Int = 31 Then tempL = Mumbai
            If Int = 32 Then tempL = NY
            If Int = 33 Then tempL = Osaka
            If Int = 34 Then tempL = Paris
            If Int = 35 Then tempL = Riyadh
            If Int = 36 Then tempL = SF
            If Int = 37 Then tempL = Santiago
            If Int = 38 Then tempL = SaoPaulo
            If Int = 39 Then tempL = Seoul
            If Int = 40 Then tempL = Shanghai
            If Int = 41 Then tempL = StPetersburg
            If Int = 42 Then tempL = Sydney
            If Int = 43 Then tempL = Taipei
            If Int = 44 Then tempL = Tehran
            If Int = 45 Then tempL = Tokyo
            If Int = 46 Then tempL = Toronto
            If Int = 47 Then tempL = Washington

            If Int = locP(0) Then
                e.Graphics.DrawImage(My.Resources.P1, New Point(tempL.Location.X, tempL.Location.Y + 10))
            End If
            If Int = locP(1) Then
                e.Graphics.DrawImage(My.Resources.P2, New Point(tempL.Location.X + 10, tempL.Location.Y + 10))
            End If
            If Int = locP(2) And nP = 3 Then
                e.Graphics.DrawImage(My.Resources.P3, New Point(tempL.Location.X + 15, tempL.Location.Y + 10))
            End If
            If Int = locP(3) And nP = 4 Then
                e.Graphics.DrawImage(My.Resources.P4, New Point(tempL.Location.X + 20, tempL.Location.Y + 10))
            End If


            If Rc(Int) = 1 Then e.Graphics.DrawImageUnscaled(My.Resources.Rcenter, New Point(tempL.Location.X - 20, tempL.Location.Y))


            If color(Int) = 1 Then e.Graphics.FillEllipse(Brushes.Blue, New Rectangle(tempL.Location.X + 10, tempL.Location.Y - 10, number(Int) * 5, number(Int) * 5))
            If color(Int) = 2 Then e.Graphics.FillEllipse(Brushes.Red, New Rectangle(tempL.Location.X + 10, tempL.Location.Y - 10, number(Int) * 5, number(Int) * 5))
            If color(Int) = 3 Then e.Graphics.FillEllipse(Brushes.Yellow, New Rectangle(tempL.Location.X + 10, tempL.Location.Y - 10, number(Int) * 5, number(Int) * 5))
            If color(Int) = 4 Then e.Graphics.FillEllipse(Brushes.Green, New Rectangle(tempL.Location.X + 10, tempL.Location.Y - 10, number(Int) * 5, number(Int) * 5))

        Next







    End Sub


  
End Class
