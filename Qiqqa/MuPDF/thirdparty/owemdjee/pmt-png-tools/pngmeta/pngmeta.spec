#
# pngmeta -- Get Metadata from PNG images
#
%define name pngmeta
%define version 1.11
%define release 1
%define prefix /usr

Summary: Display metadata information from PNG images
Name: %{name}
Version: %{version}
Release: %{release}
Copyright: Freely Distributable
Group: Applications/Graphics
Source: http://purl.org/net/dajobe/software/%{name}-%{version}.tar.gz
Vendor: Dave Beckett <Dave.Beckett@bristol.ac.uk>
URL: http://sourceforge.net/projects/pmt/
Provides: pngmeta
Requires: libpng.so.2 zlib
BuildRoot: /var/tmp/%{name}-%{version}

%description
This small filter program extracts metadata from PNG images and
displays them as either HTML, SOIF, RDF/XML or simple fields and
values.

%prep
rm -rf $RPM_BUILD_ROOT

%setup

%build
%configure --prefix=${prefix}

make

%install
if [ -d $RPM_BUILD_ROOT ]; then rm -rf $RPM_BUILD_ROOT; fi
mkdir -p $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc NEWS README
%{prefix}/man/man1/pngmeta.1*
%attr (755,root,root) %{prefix}/bin/pngmeta

%changelog