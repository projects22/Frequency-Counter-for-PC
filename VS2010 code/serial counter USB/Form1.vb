Public Class Form1
    Private Sub Form1_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        If sp1.IsOpen Then sp1.Close()
    End Sub

    Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load
        GetPorts()
    End Sub
    Sub GetPorts()
        For Each sp As String In My.Computer.Ports.SerialPortNames ' Show all available COM ports.
            cmb1.Items.Add(sp)
        Next
    End Sub
    Private Sub cmb1_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cmb1.SelectedIndexChanged
        On Error Resume Next
        sp1.PortName = cmb1.SelectedItem
        sp1.BaudRate = 1200
        sp1.DataBits = 8
        sp1.Open()
        Label1.Text = "Port is Open"
        Timer1.Enabled = True
    End Sub

    Private Sub Timer1_Tick(ByVal sender As Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Dim inB(3) As Byte
        Dim b1, b2, b3 As UInteger
        Dim freq As ULong
        Dim period As Double ', freq

        If sp1.BytesToRead > 2 Then
            sp1.Read(inB, 0, 3)
            b1 = inB(0)
            b2 = inB(1)
            b3 = inB(2)
            freq = b1 + (b2 * 256) + (b3 * 65536)
            text1.Text = FormatNumber(freq, 0)
            period = 1000000 / freq
            If freq = 0 Then period = 0
            If period < 10000 Then
                text2.Text = Format(period, "0.000")
            Else
                text2.Text = FormatNumber(period, 0)
            End If
        End If
    End Sub
End Class
