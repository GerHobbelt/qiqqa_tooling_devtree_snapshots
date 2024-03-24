<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:enx="A" xmlns:func="http://exslt.org/functions"
                 extension-element-prefixes="func">

  <xsl:output method="xml"/>
  <xsl:variable name="dDT" select="document('textopt2b.xml')/ms" />
  <func:function name="enx:CMOEACN">
    <xsl:param name="s" />
    <func:result>
       <xsl:text>c</xsl:text><xsl:value-of select="$s/@n"/>
    </func:result>
  </func:function>
  <xsl:template match="/">
    <aL>
      <xsl:for-each select="$dDT/t[@n='IABM']/m">
            <a>
              <xsl:variable name="cN" select="enx:CMOEACN(.)" />
            </a>
        </xsl:for-each>
        <xsl:for-each select="$dDT/t[@n='IABM']/m">
        <a>
          <xsl:variable name="cN" select="enx:CMOEACN(.)" />
        </a>
    </xsl:for-each>
</aL>
  </xsl:template>
</xsl:stylesheet>
