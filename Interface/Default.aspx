<%@ Page Title="Page d'accueil" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
    CodeBehind="Default.aspx.cs" Inherits="Interface._Default" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
    <h2>
        Bienvenue dans ASP.NET!
    </h2>
    <p>
        Pour en savoir plus sur ASP.NET, consultez <a href="http://www.asp.net" title="Site Web ASP.NET">www.asp.net</a>.
    </p>
    <p>
        Vous pouvez également trouver de la <a href="http://go.microsoft.com/fwlink/?LinkID=152368"
            title="Documentation ASP.NET sur MSDN">documentation sur ASP.NET sur MSDN</a>.
    </p>
    <p>
        <asp:Label id="label1" text="strike" runat="server"/>
        <asp:TextBox id="strike" runat="server"/>
    </p>
    <p>
        <asp:Label id="label11" text="sigma" runat="server"/>
        <asp:TextBox id="sigma" runat="server"/>
    </p>
    <p>
        <asp:Label id="label8" text="size" runat="server"/>
        <asp:TextBox ID="size" runat="server"></asp:TextBox>
    </p>
    <p>
        <asp:Label id="Label3" text="r" runat="server"/>
        <asp:TextBox ID="r" runat="server"></asp:TextBox>
   </p>
    <p>
        <asp:Label id="Label4" text="rho" runat="server"/>
        <asp:TextBox ID="rho" runat="server"></asp:TextBox>
    </p>
    <p>
        <asp:Label id="Label5" text="h" runat="server"/>
        <asp:TextBox ID="h" runat="server"></asp:TextBox>
    </p>
    <p>
        <asp:Label id="Label6" text="samples" runat="server"/>
        <asp:TextBox ID="samples" runat="server"></asp:TextBox>
    </p>
    <p>
        <asp:Label id="Label10" text="Prix" runat="server"/>
        <asp:Label id="Label2" text="" runat="server"/>
    </p>
    <p>
        <asp:Label id="Label7" text="IC" runat="server"/>
        <asp:Label id="Label" text="" runat="server"/>
    </p>
     <p>
        <asp:Label id="Label9" text="type" runat="server"/>
        <asp:Label id="type" text="" runat="server"/>
    </p>
    <p>
    <asp:Button id="gebtn1" text="Start" OnClick='price' runat="server"/>
    </p>
</asp:Content>
